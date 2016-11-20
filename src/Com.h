/*
 * Com.h
 *
 *  Created on: 19 nov. 2016
 *      Author: tgtob
 */

#ifndef SRC_COM_H_
#define SRC_COM_H_

#define COM_BUFF_SIZE 200

#include <Arduino.h>

class Com {
public:
	Com();
	void send();
	void out(const char * s);
	void outln(const char * s);
	virtual ~Com();
private:
	char * p_data_out;
	char data[COM_BUFF_SIZE];
	uint32_t data_out_ln;


};

#endif /* SRC_COM_H_ */
