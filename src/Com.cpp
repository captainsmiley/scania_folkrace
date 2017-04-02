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
p_data_in(data),
data_out_ln(0)
{
	#ifdef SERIAL_DEBUG
	Serial.begin(115200);
	Serial.println("Start of program");
	#endif
	Serial1.begin(115200);
}

void Com::send()
{
	size_t i = 0;
	while(send_char())
	{
		i++;
		if (i>= MAX_TX_COUNT) break;
	}
}

bool Com::send_char()
{
	if(p_data_in != p_data_out)
	{
		Serial.write(*p_data_out);
		Serial1.write(*p_data_out);
		p_data_out++;
		if(p_data_out >= data_end()) p_data_out = data_start();
		return true;
	}
	return false;
}

char * Com::data_start()
{
	return data;
}
char * Com::data_end()
{
	return data+COM_BUFF_SIZE;
}

void Com::out(const char * s)
{
	while (*s != 0) {
		out(*s);
		s++;
	}
}
void Com::out(char c)
{
		*p_data_in = c;
		p_data_in++;
		if(p_data_in >= data_end())
		{
			p_data_in = data_start();
		}
}

/*
void Com::out(String s)
{
	char  buff[22];
s.toCharArray(buff,22);
	out(buff);
}*/

void Com::outln(const char * s)
{
	out(s);
	out("\n\r");
}

Com::~Com() {
	// TODO Auto-generated destructor stub
}

