/*
 * control_and_actuate.cpp

 *
 *  Created on: 20 nov. 2016
 *      Author: tgtob
 */

#include "control_and_actuate.h"

#include "com.h"



#define PK 180
#define PK_SCALE 1000
#define S3_PK 180
#define S3_SCALE 100
#define S2_DK 50


void ControlAndActuate::control() {


	fw = map(400,0,1023,0,255);
	sensor1 = s1.getAvg(10);

	//uint32_t act_s2 = 0;
	//uint32_t act_s3 = 0;
	int pos_s2 = (int) s2.getAvg(10);
	//uint16_t old_pos_s2 = s2.getAvg(10,10);
	int pos_s3 = (int) s3.getAvg(10);
	//uint16_t old_pos_s3 = s3.getAvg(10,10);

	/*
	if(pos_s2 > 0)
	{
		act_s2 = (((uint32_t)(pos_s2 - 0)) * S2_PK ) / S2_SCALE; // + (((uint32_t)(pos_s2 - old_pos_s2)) * trim2) / S2_SCALE;

	}
	if(pos_s3 > 0)
	{
		act_s3 = (((uint32_t)(pos_s3 - 0)) * S2_PK) / S3_SCALE; //  + (((uint32_t)(pos_s3 - old_pos_s3))) * trim2 / S2_SCALE;

	}
	if (act_s3 > 1023) act_s3 = 1023;
	if (act_s2 > 1023) act_s2 = 1023;
	*/
	int act = ((pos_s2 - pos_s3) * 100)  / PK_SCALE;
	//if (act > (TURN_MAX - TURN_MID) ) act = TURN_MAX - TURN_MID;
	//if (act < (TURN_MIN - TURN_MID) ) act = TURN_MIN - TURN_MAX;

	debug_act = act;
	//debug_act_s3 = act_s3;



	if ((TURN_MID - act) < TURN_MIN )
	{
		turn_value = TURN_MIN;
	}else if((TURN_MID - act) > TURN_MAX)
	{
		turn_value = TURN_MAX;
	}
	else{

turn_value = ( TURN_MID - act) ; //- map(act_s2,0,1023,0,TURN_MID-TURN_MIN) + map(act_s3,0,1023,0,TURN_MAX-TURN_MID);
	}



	if (s1.getAvg(10)<200)
	{
		fw = map(FW_SPEED,0,1023,0,255);
		bw = 0;
	}
	else
	{
		fw = 0;
		bw = BW_SPEED;//map(trim1,0,1023,0,255);
		turn_value = TURN_MID - (turn_value - TURN_MID);
	}

	turn_value = map(500,0,1023,0,180);
	fw = map(trim2,0,1023,0,180);
	bw = 0;

	if(pms.getSpeed() > 1000)
	{
		fw= (uint8_t) map(pms.getSpeed(),1000,2000,0,255);
		bw=0;
	}else if(pms.getSpeed() < 1000)
	{
		fw=0;
		bw=(uint8_t)map(pms.getSpeed(),1000,0,0,255);
	}
	else if(pms.getSpeed() == 1000)
	{
		fw=0;
		bw=0;
	}
	else
	{
		com.out("Speed out of range");
		fw=0;
		bw=0;
	}

	turn_value = pms.getTurn();

}

void ControlAndActuate::actuate() {
	if(digitalRead(EN_PIN))
	{
		drive_active = true;
	}
	else
	{
		drive_active = false;
	}
	if (pms.getDrive())
	{
		drive_active = true;
	}
	if ((!drive_active))
	{
		fw = 0;
		bw = 0;
	}
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
	OCR4D = bw;
	OCR4B = fw;
	//analogWrite(FW_PIN,fw);
	//analogWrite(BW_PIN,bw);
}



ControlAndActuate::ControlAndActuate(uint32_t dt_p) :
Task("Control and actuate",dt_p)
{}

ControlAndActuate::~ControlAndActuate(){}

void ControlAndActuate::setup()
{

}


void ControlAndActuate::run()
{
	control();
	actuate();

}
