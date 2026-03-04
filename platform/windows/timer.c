#include "timer.h"
#include <windows.h>
#include <stdatomic.h>
#include <stdio.h>

static atomic_uint_fast8_t timer_ctrl = 0;
static atomic_uint_fast8_t timer_val  = 0;
static atomic_uint_fast8_t timer_intrr = 0;


DWORD WINAPI timer_thread(LPVOID arg) //window wayy
{
    while (1)
    {
        Sleep(1000);   

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
                    atomic_store(&timer_intrr, 1);  
                }
            }
        }
    }

    return 0;
}


void timer_init(void)
{
    CreateThread(NULL, 0, timer_thread, NULL, 0, NULL);
}

void timer_control_write(uint8_t val)
{
    atomic_store(&timer_ctrl, val);
}

void timer_val_write(uint8_t val)
{
    atomic_store(&timer_val, val);
}

uint8_t timer_val_read(void)
{
    return atomic_load(&timer_val);
}

uint8_t timer_intrr_read(void)
{
    return atomic_load(&timer_intrr);
}

void timer_intrr_clear(void)
{
    atomic_store(&timer_intrr, 0);
}