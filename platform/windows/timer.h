
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>


void timer_init(void);
void timer_control_write(uint8_t val);
void timer_val_write(uint8_t val);
uint8_t timer_val_read(void);
uint8_t timer_intrr_read(void);
void timer_intrr_clear(void);

#endif