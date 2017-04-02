/*
 * readSensors.h
 *
 *  Created on: 20 nov. 2016
 *      Author: tgtob
 */

#ifndef SRC_READSENSORS_H_
#define SRC_READSENSORS_H_

#include "Task.h"
#include "globals.h"


class ReadSensors : public Task
{
public:
	ReadSensors(uint32_t dt_p);
	virtual ~ReadSensors();

	virtual void setup() final;
	virtual void run() final;

};



#endif /* SRC_READSENSORS_H_ */
