#ifndef SCHEDULER_TG
#define SCHEDULER_TG

#include "TgTimer3.h"
#include "task.h"


class TgScheculer
{
  static TgTimer3 t3;

public:
  TgScheculer();
  static uint16_t int_count;
  void setup();
  void setup_timer();
  friend class TgTimer3;
  void add_task(Task t);
  bool task_ovf();
  String name_of_ovf_task();
  void print_exe_times();

protected:
  static void main_tick();


private:

  static uint8_t task_count;
  static Task task_vec [];







};















#endif
