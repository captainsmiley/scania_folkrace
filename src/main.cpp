#include <Arduino.h>
#include <Servo.h>
#include "Timer4.h"
#include "settings.h"
#include "scheduler.h"
#include "SensorData.h"
#include "Com.h"
#include "globals.h"
#include "control_and_actuate.h"
#include "readSensors.h"
#include "Parameters.h"



void detect_standstill()
{
	uint16_t dev = s2.getDev(50) + s3.getDev(50);
	if(dev > 100) dev = 100;
	FW_SPEED = map(dev,100,0,360,520);

}


char buff [20];



const char b_msg[] PROGMEM = {"button pressed "};
void check_button()
{

	if(digitalRead(BUTTON_PIN)==0)
	{
		com.out(b_msg);
	}


}
void print_exe_times()
{
		com.out("Execute Times: ");
	for(int i=0; i< s.get_task_count(); ++i)
	{
		com.out(s.get_task(i).name);
		com.out(" ");
String(s.get_task(i).exe_time_max).toCharArray(buff,20);
		com.out(buff);
		com.out(", ");
	}
	com.outln("");
}

void print_info()
{
#define L_BUFF_SIZE 50
	char l_buff[L_BUFF_SIZE];
	static int sec = 0;
	static uint16_t old_count = 0;
	uint16_t count = s.int_count;

	if (count-old_count != 1000)
	{
		com.out("Warning! ");
	com.out("Delta int_count: ");
    //com.out(String(count-old_count));
	com.outln("");
	}
	old_count = count;
	sec++;
	com.out("Time: ");
	//itoa(100,l_buff,10);
	com.out(itoa(sec,l_buff,10));
	com.outln("s");

	print_exe_times();
	com.out("Sensor values: ");
	//com.out("Trim1: " + String(trim1) + " ");
	//com.out("Trim2: " + String(trim2) + " ");
	//com.out("sensor1: " + String(s1.getAvg(10)) + " ");
	//com.out("sensor2: " + String(s2.getAvg(10)) + " ");
	//com.out("sensor3: " + String(s3.getAvg(10)) + " ");
	com.outln("");
	com.out("Actuation: ");
	//com.out("FW: " + String(fw) + " ");
	//com.out("BW: " + String(bw) + " ");
	//com.out("Turn: " + String(turn_value));
	com.outln("");
	com.outln("**** Parameters: ****");
	//com.out("Speed = "+String(pms.getSpeed()) + " ");
	com.out("Turn = ");//com.out(itoa(634,l_buff,10)); com.out(" ");
	com.out(itoa(pms.getTurn(),l_buff,10));
    //com.out("Turn = ");//com.out(itoa(pms.getTurn(),l_buff,10)); com.out(" ");
	com.outln("");
	com.outln("**************************************");

}


void check_serial1()
{
	char c;
	static char param[110] = {""};
	static char value[110] = {""};
	static uint8_t value_index = 0;
	static uint8_t param_index = 0;
	static int count = 0;
	static enum State {READ_PARAM,READ_VALUE,SEARCH} state;
	while (Serial1.available() > 0) {
		// read the incoming byte:
		c = Serial1.read();
		switch (state)
		{
		case READ_PARAM:
			count++;
			if(c=='='){count = 0; value[0] = '\0'; state = READ_VALUE;}
			else if(c=='&') {count = 0;param[0] = '\0';}
			else
				{
				param[param_index] = c;
				param_index++;
				param[param_index] = '\0';
				}
			break;
		/* Reading value from serial *** */
		case READ_VALUE:
			if(c=='=') {
				value[0] = '\0';
			}
			else if(c=='&'){
				Serial.println("Found param value:");
				Serial.print(param);Serial.print(value);
				pms.try_write(param,value);
				//param[0] = '\0' ; state = READ_PARAM;
				//value[0] = '\0';
			}
			else
			{
				value[value_index] = c;
			value[++value_index] = '\0';
			}
			break;

		/*****              Searching for & *************/
		case SEARCH:
			if(c=='&'){
				param[0] = '\0';
				value[0] = '\0';
				state = READ_PARAM;
			}
			break;
		}


		com.out(c);
		//Serial.print(c);
	}
}

void send_serial()
{
	//com.send();
}

void send_data()
{
	com.out("&test=1&");

}

void clear_client_mode()
{
	pms.setClientMode(Parameters::OFFLINE);
}

ControlAndActuate ca(40);
ReadSensors rs(20);
Task     pi("print info",1000,&print_info);
Task     cs1("check_serial1",100,&check_serial1);
Task     send_s("send_serial",10,&send_serial);
Task     clear_c_mode("clear_c_mode",300,&clear_client_mode);
Task     send_data_t("send_data",200,&send_data);

void setup()
{
	//Wire.begin();
	//tof.device_init();
	Serial1.begin(115200);
	noInterrupts();
	//tof_sensor.init();
	//tof_sensor.setMeasurementTimingBudget(50);
	//tof_sensor.setTimeout(500);
	pinMode(EN_PIN,INPUT);
	pinMode(BUTTON_PIN,INPUT_PULLUP);

	ca.setup();


	t4.setup();
	s.setup_timer();
	s.add_task(rs);
	s.add_task(pi);
	s.add_task(ca);
	s.add_task(cs1);
	//s.add_task(send_s);
	//s.add_task(clear_c_mode);
	//s.add_task(send_data_t);


	interrupts();
	turn.attach(TURN_PIN);
	turn.write(turn_value);

	//tof.Device_info();

	//tof_sensor.startContinuous(100);

}


void loop()
{
	//com.outln("Main loop start");
	if (s.task_ovf()) {
		Serial.println("Task has ovf!!");
		//com.outln("Task has ovf!!!");
	}
	//delay(100);
	com.send();
	/*
	//debug_print("Act_s2: " + String(debug_act));
	//debug_print("Act_s3: " + String(debug_act_s3));
	debug_print("Dev: " + String(s2.getDev(50)+s3.getDev(50)));
	//debug_print("EN_PIN: " + String(digitalRead(EN_PIN)));
	debug_print("FW_SPEED: " + String(FW_SPEED));
	for(int i=0; i<10; ++i)
	debug_print("sensor1 prev: " + String(s1.get(i)));

	//s.print_exe_times();


	//check_button();

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
	//delay(500);
	//debug_print("Loop Time: " + String(s.int_count-start));
	//debug_print(String(OCR3A));
	//debug_print("T_int: " + String(s.int_count));

	 */
	//check_button();


}
