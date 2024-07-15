#ifndef FRAMES_H
#define FRAMES_H

#include "config.h"
#include "led.h"
#include "table.h"
#include "led_matrix_color_data.h"

void display_frame(uint32_t* frame, int len);
void stop_frames();
void start_frames();
void toggle_frames();

#endif