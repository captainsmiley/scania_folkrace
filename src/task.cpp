#include "task.h"

Task::Task (char const * name_p, uint32_t dt_p, TASK_FP fp_p) :
dt(dt_p),
running(false),
ovf(false),
exe_time(0),
exe_time_max(0),
name(name_p),
fp(fp_p)
{}
