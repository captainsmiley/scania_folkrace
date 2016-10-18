#include <Arduino.h>
#include <Servo.h>
#include "settings.h"
#include "tgtimer3.h"
#include "scheduler.h"
#define __ASSERT_USE_STDERR
#include <assert.h>

Servo turn;
uint8_t turn_value = 90;
uint8_t fw = 0;
uint8_t bw = 0;

int sensor1 = -1;
int trim1 = -1;
int trim2 = -1;
bool t4_int = false;

//uint32_t int_count = 0;
TgScheculer s;

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


void timer3_ovf_int()
{
	//int_count++;
}

void readSensors() {
	sensor1 = analogRead(SENSOR1_PIN);
	#if TRIM1
	trim1 = analogRead(TRIM1_PIN);
	#endif
	#if TRIM2
	trim2 = analogRead(TRIM2_PIN);
	#endif
}

void actuate() {
	assert(bw==0 || fw==0);
	assert(turn_value<=180);
	turn.write(turn_value);
	OCR4D = fw;
	//analogWrite(FW_PIN,fw);
	//analogWrite(BW_PIN,bw);
}




void control() {
	turn_value = map(trim2,0,1023,0,180);
	fw = map(trim1,0,1023,0,255);
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
	debug_print(String("Sec: ") + String(secounds)  );
	/*
	for(uint32_t i=0; i< 3000 ; ++i)
	{
		readSensors();
	}
	*/
	//delay(500);
	//debug_print("Sec loop done");
}


// PD7 (T0/OC4D/ADC10) on pro micro D6
// PC6 (OC3A/OC4A) on pro micro D5
/*
CS43 CS42 CS41 CS40 Asynchronous Clocking Mode Synchronous Clocking Mode
0 0 0 0 T/C4 stopped T/C4 stopped
0 0 0 1 PCK CK
0 0 1 0 PCK/2 CK/2
0 0 1 1 PCK/4 CK/4
0 1 0 0 PCK/8 CK/8
0 1 0 1 PCK/16 CK/16
0 1 1 0 PCK/32 CK/32
0 1 1 1 PCK/64 CK/64
1 0 0 0 PCK/128 CK/128
1 0 0 1 PCK/256 CK/256
1 0 1 0 PCK/512 CK/512
1 0 1 1 PCK/1024 CK/1024
1 1 0 0 PCK/2048 CK/2048
1 1 0 1 PCK/4096 CK/4096
1 1 1 0 PCK/8192 CK/8192
1 1 1 1 PCK/16384 CK/16384

f = (16 000 000 / X) / 512

*/
void setup()
{
	noInterrupts();
	turn.attach(TURN_PIN);
	turn.write(turn_value);
	#if SERIAL_DEBUG
	Serial.begin(115200);
	Serial.println("Start of program");
	#endif

	pinMode(6,OUTPUT);

	TCCR4B |= (1<<CS43) | (1<<CS42) | (1<<CS41) | (1<<CS40);
	TCCR4B &= ~(1<<CS43) & ~(0<<CS42) & ~(1<<CS41) & ~(1<<CS40);
	TCCR4B |= (1<<PSR4); // reset presc

	TCCR4D = (0<<WGM41) | (1<<WGM40); // Phase and Frequency Correct PWM
	//TIMSK4 = (1<<TOIE4);

	//OC4D pin connected
	//TCCR4C &= ~(1<<COM4D1);
	TCCR4C = (1<<COM4D1) | (1<<COM4D0) | (1<<PWM4D);

	TCCR4E &= ~(1<<TLOCK4) & ~(1<<ENHC4);
	OCR4D = 10;
	//TCCR4E |= (1<<OC4OE5);

	s.setup_timer();
	s.add_task(Task("fast",10,&RunEvery10ms));
	s.add_task(Task("slow",1000,&RunEverySec));




	interrupts();

	}







void loop()
{
	debug_print("Main loop start");
	if (s.task_ovf()) {
		debug_print("Task has ovf!!!");
	}
	debug_print("Trim1: " + String(trim1));
	s.print_exe_times();

	/*
	uint32_t start = s.int_count;
	/*
	debug_print("Main loop start");
	Serial.println(OCR3A);
	debug_print("T_int: " + String(int_count));
	readSensors();
	debug_print("Trim: " + String(trim));


	control();
	debug_print("FW: " + String(fw));

	actuate();
*/
	delay(5000);
	//debug_print("Loop Time: " + String(s.int_count-start));
	//debug_print(String(OCR3A));
	//debug_print("T_int: " + String(s.int_count));


}

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
    // transmit diagnostic informations through serial link.
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    //Serial.flush();
    // abort program execution.
    //abort();
		while (true) ;
			/* code */

}
