#include "../main.h"
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

void* timer_thread(void *_arg);
void timer_control_write(u8 val);
void timer_val_write(u8 val);
u8 timer_val_read();
void timer_init();
