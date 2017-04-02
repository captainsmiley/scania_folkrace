/*
 * Com.h
 *
 *  Created on: 19 nov. 2016
 *      Author: tgtob
 */

#ifndef SRC_COM_H_
#define SRC_COM_H_

#define COM_BUFF_SIZE 800
#define MAX_TX_COUNT 5

#include <Arduino.h>

class Com {
public:
	Com();
	void send();
	bool send_char();
	void out(const char * s);
	void out(char c);
	//void out(String s);
	void outln(const char * s);
	void out1(const char * s);
	void out1(char c);
	//void out1(String s);
	void outln1(const char * s);
	virtual ~Com();
private:
	volatile char * p_data_out;
	volatile char * p_data_in;
	char data[COM_BUFF_SIZE];
	char * data_start();
	char * data_end();
	uint32_t data_out_ln;


};

#endif /* SRC_COM_H_ */
