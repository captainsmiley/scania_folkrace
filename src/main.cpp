#include <Arduino.h>
#include <Servo.h>
#include "Timer4.h"
#include "settings.h"
#include "scheduler.h"
#include "SensorData.h"



// Global objects
Servo turn;
Timer4 t4;
Scheduler s;
SensorData<uint16_t> s1(100);

// Global variables
uint8_t turn_value = 90;
uint8_t fw = 0;
uint8_t bw = 0;
uint16_t sensor1 = 0;
int trim1 = -1;
int trim2 = -1;


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
	#if TRIM1
	trim1 = analogRead(TRIM1_PIN);
	#endif
	#if TRIM2
	trim2 = analogRead(TRIM2_PIN);
	#endif
}

void actuate() {
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
	OCR4D = fw;
	OCR4A = bw;
	//analogWrite(FW_PIN,fw);
	//analogWrite(BW_PIN,bw);
}




void control() {
	turn_value = map(trim2,0,1023,0,180);
	fw = map(trim1,0,1023,0,255);

	sensor1 = s1.getAvg(10);

	if (sensor1<400)
	{
		fw = map(sensor1,400,0,0,255);
	}
}

void controlAndActuate()
{
	control();
	actuate();
}

void RunEvery10ms()
{
	readSensors();
	control();
	actuate();
}

void RunEverySec()
{

	static uint32_t secounds = 0;
	secounds++;
	//debug_print(String("Sec: ") + String(secounds)  );


	//delay(500);
	//debug_print("Sec loop done");
}





void setup()
{
	noInterrupts();
	turn.attach(TURN_PIN);
	turn.write(turn_value);
	#if SERIAL_DEBUG
	Serial.begin(115200);
	Serial.println("Start of program");
	#endif

	t4.setup();
	s.setup_timer();
	s.add_task(Task("readSensors",4,&readSensors));
	s.add_task(Task("controlAndActuate",10,&controlAndActuate));

	interrupts();

}







void loop()
{
	debug_print("Main loop start");
	if (s.task_ovf()) {
		debug_print("Task has ovf!!!");
	}
	debug_print("Trim1: " + String(trim1));
	debug_print("Trim2: " + String(trim2));
	debug_print("sensor1: " + String(sensor1));
	for(int i=0; i<10; ++i)
	debug_print("sensor1 prev: " + String(s1.get(i)));
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
*/
	delay(500);
	//debug_print("Loop Time: " + String(s.int_count-start));
	//debug_print(String(OCR3A));
	//debug_print("T_int: " + String(s.int_count));


}
