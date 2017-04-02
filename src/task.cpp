#include "task.h"

Task::Task (char const * name_p, uint16_t dt_p, TASK_FP fp_p) :
dt(dt_p),
running(false),
queued(false),
ovf(false),
exe_time(0),
exe_time_max(0),
name(name_p),
started_time(0),
stoped_time(0),
counter(0),
fp(fp_p)
{}

Task::Task (char const * name_p, uint16_t dt_p) :
dt(dt_p),
running(false),
queued(false),
ovf(false),
exe_time(0),
exe_time_max(0),
name(name_p),
started_time(0),
stoped_time(0),
counter(0),
fp(nullptr)
{}

uint8_t Task::tick(){
	counter++;
	if(counter >= dt){
		if(queued) return 1;
		queued = true;
		counter = 0;
	}
	return 0;
}

Task::~Task(){}

void Task::setup()
{

}

void Task::run()
{
	if (fp)
	fp();
}
