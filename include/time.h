#ifndef _TIME_H
#define _TIME_H

#include <Arduino.h>
bool is_new_frame_time();
bool is_new_sim_time();
void set_sim_ms(unsigned long ms);

#endif