/*
 * Com.cpp
 *
 *  Created on: 19 nov. 2016
 *      Author: tgtob
 */

#include <Com.h>
#include <Arduino.h>

Com::Com() :
p_data_out(data),
data_out_ln(0)
{
	#ifdef SERIAL_DEBUG
	Serial.begin(115200);
	Serial.println("Start of program");
	#endif
}

void Com::send()
{
	if (data_out_ln > 0)
	{
	Serial.write(data,data_out_ln);
	data_out_ln = 0;
	}
}
void Com::out(const char * s)
{
	while (*s != 0) {
		data[data_out_ln] = *s;
		s++;
		data_out_ln++;
		if(data_out_ln >= COM_BUFF_SIZE)
		{
			data_out_ln = 0;
			outln("Error com of");
		}
	}
	data[data_out_ln] = '\0';
}

void Com::outln(const char * s)
{
	out(s);
	out("\n\r");
}

Com::~Com() {
	// TODO Auto-generated destructor stub
}

