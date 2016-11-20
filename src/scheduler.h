#ifndef SCHEDULER_TG
#define SCHEDULER_TG

#include "timer3.h"
#include "task.h"


class Scheduler
{
  static Timer3 t3;

public:
  Scheduler();
  static uint16_t int_count;
  void setup();
  void setup_timer();
  friend class Timer3;
  void add_task(Task t);
  bool task_ovf();
  String name_of_ovf_task();
  const Task& get_task(uint8_t n) const;
  uint8_t get_task_count() const;
  void print_exe_times();
protected:
  static void main_tick();
private:
  static uint8_t task_count;
  static Task task_vec [];
};















#endif
