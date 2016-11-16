/*
 * Timer4.cpp
 *
 *  Created on: 30 okt. 2016
 *      Author: tgtob
 */

#include <Timer4.h>
#include <Arduino.h>
#include "settings.h"

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
Timer4::Timer4() {
	// TODO Auto-generated constructor stub

}
void Timer4::setup()
{
	pinMode(FW_PIN,OUTPUT);
	pinMode(BW_PIN,OUTPUT);

	TCCR4B |= (1<<CS43) | (1<<CS42) | (1<<CS41) | (1<<CS40);
	TCCR4B &= ~(1<<CS43) & ~(0<<CS42) & ~(1<<CS41) & ~(1<<CS40);
	TCCR4B |= (1<<PSR4); // reset presc

	TCCR4D = (0<<WGM41) | (1<<WGM40); // Phase and Frequency Correct PWM
	//TIMSK4 = (1<<TOIE4);

	//OC4D pin connected
	//TCCR4C &= ~(1<<COM4D1);
	OCR4D = 0;
	TCCR4C = (1<<COM4D1) | (0<<COM4D0) | (1<<PWM4D);
	TCCR4C &= ~(0<<COM4D1) & ~(1<<COM4D0) & ~(0<<PWM4D);

	OCR4B = 0;
	TCCR4A = (1<<COM4B1) | (0<<COM4B0) | (1<<PWM4B);
	TCCR4A &= ~(0<<COM4B1) & ~(1<<COM4B0) & ~(0<<PWM4B);


	TCCR4E &= ~(1<<TLOCK4) & ~(1<<ENHC4);
	//TCCR4E |= (1<<OC4OE5);

}

Timer4::~Timer4() {
	// TODO Auto-generated destructor stub
}

