#include "../timer.h"

atomic_uint_fast8_t timer_ctrl = 0;
atomic_uint_fast8_t timer_val  = 0;

void* timer_thread(void *_arg)
{
	while (1)
	{
		fflush(stdout);
		// TODO: make it cross-platform by removing usleep
		usleep(1000000); // 1 second

		uint8_t ctrl = atomic_load(&timer_ctrl);
		if (ctrl & 0x80)
		{
			uint8_t val = atomic_load(&timer_val);

			if (val > 0)
			{
				val--;
				atomic_store(&timer_val, val);

				if (val == 0)
				{
					// maybe interrupt TODO

				}

			}
		}
	}

	return NULL;
}	


void timer_control_write(u8 val){
	atomic_store(&timer_ctrl, val);
}

u8 timer_val_read(){
	return atomic_load(&timer_val);
}

void timer_val_write(int val)
{
	atomic_store(&timer_val,val);
}

void timer_init()
{
	pthread_t t;
	pthread_create(&t, NULL, timer_thread, NULL);
}

