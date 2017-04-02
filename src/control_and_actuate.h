/*
 * control.h
 *
 *  Created on: 20 nov. 2016
 *      Author: tgtob
 */

#ifndef SRC_CONTROL_AND_ACTUATE_H_
#define SRC_CONTROL_AND_ACTUATE_H_

#include "globals.h"
#include "task.h"
#include "Parameters.h"
//void control_and_actuate();

class ControlAndActuate : public Task
{
public:
	ControlAndActuate(uint32_t dt_p);
	virtual ~ControlAndActuate();

	void control();
	void actuate();
	virtual void setup() final;
	virtual void run() final;


};



#endif /* SRC_CONTROL_AND_ACTUATE_H_ */
