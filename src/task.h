#ifndef TASK_TG
#define TASK_TG
#include <Arduino.h>
class Task
{
public:
  typedef void(*TASK_FP)();
  Task(char const * name_p, uint16_t dt,TASK_FP fp);
  Task(char const * name_p, uint16_t dt);
  uint8_t tick();
  virtual ~Task();
	virtual void setup();
	virtual void run();
  uint16_t dt;
  TASK_FP fp;
  bool running;
  bool ovf;
  bool queued;
  int exe_time;
  int started_time;
  int stoped_time;
  int exe_time_max;
  char const * name;

private:
  uint16_t counter;
};



#endif
