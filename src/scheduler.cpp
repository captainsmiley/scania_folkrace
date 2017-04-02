#include "scheduler.h"

Scheduler::Scheduler()
{
  //setup_timer();
}
uint16_t Scheduler::int_count = 0;
Timer3 Scheduler::t3;
uint8_t Scheduler::task_count = 0;
Task* Scheduler::task_vec[10] =
		{
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr

		};


void Scheduler::main_tick()
{
	t3.set_ocr_interrupt(false);
	interrupts();
	int_count++;

	// Check tasks to be queued
	for (uint8_t i=0;i<task_count;++i)
	{
		if (task_vec[i]->tick())
			{
			Serial.print("ERROR OVF");
			Serial.println(task_vec[i]->name);
			t3.set_ocr_interrupt(false);
			return;
			}

		/*
		if (int_count % task_vec[i]->dt == 0 )
		{
			if (task_vec[i]->queued)
			{
				task_vec[i]->ovf = true;
				continue;
			}
			else
			{
				task_vec[i]->queued = true;
			}

		}
		*/

	}


	// Run tasks in queue
	for (uint8_t i=0;i<task_count;++i)
	{


		if (task_vec[i]->queued && !task_vec[i]->running)
		{
			task_vec[i]->started_time = int_count;
			task_vec[i]->running = true;
			task_vec[i]->queued = false;
			t3.set_ocr_interrupt(true);
			task_vec[i]->run();   // run task
			t3.set_ocr_interrupt(false);
			task_vec[i]->running = false;
			task_vec[i]->exe_time = int_count-task_vec[i]->started_time;
			if (task_vec[i]->exe_time > task_vec[i]->exe_time_max) task_vec[i]->exe_time_max = task_vec[i]->exe_time;
		}
	}
t3.set_ocr_interrupt(true);

}
void Scheduler::setup()
{
  task_count = 0;

}

void Scheduler::add_task(Task &t)
{
  if (task_count >= 10) return;
  task_vec[task_count] = &t;
  task_count++;
}
bool Scheduler::task_ovf()
{
  for(uint8_t i=0;i<task_count;++i)
  {
    noInterrupts();
    if(task_vec[i]->ovf) return true;
    interrupts();
  }
  return false;
}
String Scheduler::name_of_ovf_task()
{
  for(uint8_t i=0;i<task_count;++i)
  {
    if(task_vec[i]->ovf) return task_vec[i]->name;
  }
  return "no";
}

void Scheduler::print_exe_times()
{

	t3.set_ocr_interrupt(false);
  for(uint8_t i=0;i<task_count;++i)
  {
	Serial.println("Execution times");
    Serial.println(task_vec[i]->name + String(task_vec[i]->exe_time));
  }
  t3.set_ocr_interrupt(true);
}

const Task& Scheduler::get_task(uint8_t n) const
{
	return *task_vec[n];
}

uint8_t Scheduler::get_task_count() const
{
	return task_count;
}

void Scheduler::setup_timer()
{
	t3.set_ocr_interrupt(&main_tick);
	t3.set_mode(Timer3::CTC_OCR);
	t3.set_dt_ocr(1);
	t3.set_ocr_interrupt(true);
	//t3.set_ocr_interrupt(false);
	//t3.set_ocr_interrupt(true);
}
