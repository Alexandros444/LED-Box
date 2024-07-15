#ifndef FRAMES_H
#define FRAMES_H

#include "config.h"
#include "led.h"
#include "table.h"
#include "led_matrix_data.h"
#include "led_matrix_color_data.h"

uint32_t* frames[] = { test_color, black_color, white_color, I_color, K_color, A_color };
size_t frame_sizes[] = { test_color_size, black_color_size, white_color_size, I_color_size, K_color_size, A_color_size };
int i_frame = 0;

void display_frame(uint32_t* frame, int len);

#endif