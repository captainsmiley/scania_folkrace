#include "scheduler.h"

Scheduler::Scheduler()
{
  //setup_timer();
}
uint16_t Scheduler::int_count = 0;
Timer3 Scheduler::t3;
uint8_t Scheduler::task_count = 0;
Task Scheduler::task_vec[5] = {
  Task("",0,NULL),
  Task("",0,NULL),
  Task("",0,NULL),
  Task("",0,NULL),
  Task("",0,NULL)
};


void Scheduler::main_tick()
{
  int_count++;
  for (uint8_t i=0;i<task_count;++i)
  {
    if (int_count % task_vec[i].dt == 0 )
    {
      if (task_vec[i].running)
      {
        task_vec[i].ovf = true;
        continue;
      }
      int old_int_count = int_count;
      task_vec[i].running = true;
      interrupts();
      task_vec[i].fp();
     // noInterrupts();
      task_vec[i].running = false;
      task_vec[i].exe_time = int_count-old_int_count;
    }
  }

  //if (int_count > 10000) int_count = 0;
}
void Scheduler::setup()
{
  task_count = 0;

}

void Scheduler::add_task(Task t)
{
  if (task_count >= 5) return;
  task_vec[task_count] = t;
  task_count++;
}
bool Scheduler::task_ovf()
{
  for(uint8_t i=0;i<task_count;++i)
  {
    noInterrupts();
    if(task_vec[i].ovf) return true;
    interrupts();
  }
  return false;
}
String Scheduler::name_of_ovf_task()
{
  for(uint8_t i=0;i<task_count;++i)
  {
    if(task_vec[i].ovf) return task_vec[i].name;
  }
  return "no";
}

void Scheduler::print_exe_times()
{
  for(uint8_t i=0;i<task_count;++i)
  {
    Serial.println(task_vec[i].name + String(task_vec[i].exe_time));
  }
}

void Scheduler::setup_timer()
{
	t3.set_ocr_interrupt(&main_tick);
	t3.set_mode(Timer3::CTC_OCR);
	t3.set_dt_ocr(1);
	t3.set_ocr_interrupt(true);
}
