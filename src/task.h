#ifndef TASK_TG
#define TASK_TG
#include <Arduino.h>
class Task
{
public:
  typedef void(*TASK_FP)();
  Task(String name_p, uint32_t dt,TASK_FP fp);
  uint32_t dt;
  TASK_FP fp;
  bool running;
  bool ovf;
  int exe_time;
  String name;
};



#endif
