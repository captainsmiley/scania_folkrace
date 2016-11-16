#include <Arduino.h>
#include <Servo.h>
#include "Timer4.h"
#include "settings.h"
#include "scheduler.h"
#include "SensorData.h"

#include <Tofsensor.h>
//#include <VL53L0X.h>
#include <Wire.h>



// Global objects
Servo turn;
Timer4 t4;
Scheduler s;
SensorData<uint16_t> s1(100);
SensorData<uint16_t> s2(100);
SensorData<uint16_t> s3(100);
bool drive_active = true;
//VL53L0X tof_sensor;
Tof_sensor tof;

// Global variables
int turn_value = 90;
uint8_t fw = 0;
uint8_t bw = 0;

uint16_t FW_SPEED = 400;
uint16_t sensor1 = 0;
int trim1 = -1;
int trim2 = -1;

int debug_act = 0;
uint16_t debug_act_s3 = 0;
uint16_t debug_dev_s1 = 0;


void debug_print(const char * s) {
	#if SERIAL_DEBUG
	Serial.println(s);
	#endif
}
void debug_print(String s) {
	#if SERIAL_DEBUG
	Serial.println(s);
	#endif
}


void readSensors() {
	s1.add(analogRead(SENSOR1_PIN));
	s2.add(analogRead(SENSOR2_PIN));
	s3.add(analogRead(SENSOR3_PIN));
	#if TRIM1
	trim1 = analogRead(TRIM1_PIN);
	#endif
	#if TRIM2
	trim2 = analogRead(TRIM2_PIN);
	#endif
}

void actuate() {
	if(digitalRead(EN_PIN))
	{
		drive_active = true;
	}
	else
	{
		drive_active = false;
	}
	if ((!drive_active))
	{
		fw = 0;
		bw = 0;
	}
	if (bw!=0 && fw!=0)
	{
		debug_print("actuate error");
		return;
	};
	if (turn_value>180)
	{
		debug_print("actuate error");
		return;
	}
	turn.write(turn_value);
	OCR4D = bw;
	OCR4B = fw;
	//analogWrite(FW_PIN,fw);
	//analogWrite(BW_PIN,bw);
}

void detect_standstill()
{
	uint16_t dev = s2.getDev(50) + s3.getDev(50);
	if(dev > 100) dev = 100;
	FW_SPEED = map(dev,100,0,360,520);

	/*
	static uint8_t count_boost = 0;
	static uint8_t count_slow = 0;

	uint16_t dev_s1 = s1.getDev(50);
	uint16_t dev_s2 = s2.getDev(50);
	uint16_t dev_s3 = s3.getDev(50);
	debug_dev_s1 = dev_s1;
	//debug_dev_s1 = 10;
	if((dev_s2 + dev_s3) < 50 )
	{
		count_boost = 0;
		if (count_slow >= 10) FW_SPEED = 520;
		else count_slow++;
	}
	else
	{
		count_slow = 0;

		if (count_boost >= 2)
		{
		FW_SPEED = 400;
		}
		else
		{
		count_boost++;
		}
	}
	*/

}

#define PK 180
#define PK_SCALE 1000
#define S3_PK 180
#define S3_SCALE 100
#define S2_DK 50


void control() {


	fw = map(400,0,1023,0,255);

	sensor1 = s1.getAvg(10);

	uint32_t act_s2 = 0;
	uint32_t act_s3 = 0;
	int pos_s2 = (int) s2.getAvg(10);
	uint16_t old_pos_s2 = s2.getAvg(10,10);
	int pos_s3 = (int) s3.getAvg(10);
	uint16_t old_pos_s3 = s3.getAvg(10,10);

	/*
	if(pos_s2 > 0)
	{
		act_s2 = (((uint32_t)(pos_s2 - 0)) * S2_PK ) / S2_SCALE; // + (((uint32_t)(pos_s2 - old_pos_s2)) * trim2) / S2_SCALE;

	}
	if(pos_s3 > 0)
	{
		act_s3 = (((uint32_t)(pos_s3 - 0)) * S2_PK) / S3_SCALE; //  + (((uint32_t)(pos_s3 - old_pos_s3))) * trim2 / S2_SCALE;

	}
	if (act_s3 > 1023) act_s3 = 1023;
	if (act_s2 > 1023) act_s2 = 1023;
	*/
	int act = ((pos_s2 - pos_s3) * 100)  / PK_SCALE;
	//if (act > (TURN_MAX - TURN_MID) ) act = TURN_MAX - TURN_MID;
	//if (act < (TURN_MIN - TURN_MID) ) act = TURN_MIN - TURN_MAX;

	debug_act = act;
	//debug_act_s3 = act_s3;



	if ((TURN_MID - act) < TURN_MIN )
	{
		turn_value = TURN_MIN;
	}else if((TURN_MID - act) > TURN_MAX)
	{
		turn_value = TURN_MAX;
	}
	else{

turn_value = ( TURN_MID - act) ; //- map(act_s2,0,1023,0,TURN_MID-TURN_MIN) + map(act_s3,0,1023,0,TURN_MAX-TURN_MID);
	}



	if (s1.getAvg(10)<200)
	{
		fw = map(FW_SPEED,0,1023,0,255);
		bw = 0;
	}
	else
	{
		fw = 0;
		bw = BW_SPEED;//map(trim1,0,1023,0,255);
		turn_value = TURN_MID - (turn_value - TURN_MID);
	}

	//turn_value = map(trim2,0,1023,0,180);
}

void controlAndActuate()
{
	control();
	actuate();
}







void setup()
{
	//Wire.begin();
	noInterrupts();
	#if SERIAL_DEBUG
	Serial.begin(115200);
	Serial.println("Start of program");
	#endif
	//tof_sensor.init();
	//tof_sensor.setMeasurementTimingBudget(50);
	//tof_sensor.setTimeout(500);
	pinMode(EN_PIN,INPUT);



	t4.setup();
	s.setup_timer();
	s.add_task(Task("readSensors",4,&readSensors));
	s.add_task(Task("controlAndActuate",40,&controlAndActuate));
	s.add_task(Task("detect_standstill",300,&detect_standstill));

	interrupts();
	turn.attach(TURN_PIN);
	turn.write(turn_value);
	//tof_sensor.startContinuous(100);

}







void loop()
{
	debug_print("Main loop start");
	if (s.task_ovf()) {
		debug_print("Task has ovf!!!");
	}
	debug_print("Trim1: " + String(trim1));
	debug_print("Trim2: " + String(trim2));
	debug_print("sensor1: " + String(s1.getAvg(10)));
	debug_print("sensor2: " + String(s2.getAvg(10)));
	debug_print("sensor3: " + String(s3.getAvg(10)));
	debug_print("FW: " + String(fw));
	debug_print("BW: " + String(bw));
	debug_print("Turn: " + String(turn_value));
	//debug_print("Act_s2: " + String(debug_act));
	//debug_print("Act_s3: " + String(debug_act_s3));
	debug_print("Dev: " + String(s2.getDev(50)+s3.getDev(50)));
	//debug_print("EN_PIN: " + String(digitalRead(EN_PIN)));
	debug_print("FW_SPEED: " + String(FW_SPEED));
	/*
	for(int i=0; i<10; ++i)
	debug_print("sensor1 prev: " + String(s1.get(i)));
	*/
	s.print_exe_times();

	/*
	uint32_t start = s.int_count;
	debug_print("Main loop start");
	Serial.println(OCR3A);
	debug_print("T_int: " + String(int_count));
	readSensors();
	debug_print("Trim: " + String(trim));


	control();
	debug_print("FW: " + String(fw));

	actuate();
	Serial.print(tof_sensor.readRangeContinuousMillimeters());
	  if (tof_sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

	  Serial.println();
*/
	delay(500);
	//debug_print("Loop Time: " + String(s.int_count-start));
	//debug_print(String(OCR3A));
	//debug_print("T_int: " + String(s.int_count));


}
