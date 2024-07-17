#ifndef TIMING_H
#define TIMING_H

#include <Arduino.h>
bool is_new_frame_time();
// void set_sim_ms(unsigned long ms);

void tick();
void tock(String msg);
void tockTick(String msg);

#endif