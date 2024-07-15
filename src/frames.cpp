#include "frames.h"

uint32_t* frames[] = { test_color, black_color, white_color, I_color, K_color, A_color };
size_t frame_sizes[] = { test_color_size, black_color_size, white_color_size, I_color_size, K_color_size, A_color_size };
int i_frame = 0;
bool is_i_run = true;

void stop_frames() {
	is_i_run = false;
}
void start_frames() {
	is_i_run = true;
}
void toggle_frames() {
	is_i_run = !is_i_run;
}


void display_frame(uint32_t* frame, int len) {
	// float brightness_scale = ((float)brightness) / 255;
	for (int i = 0; i < NUM_PIXELS && i < len; i++) {
		uint8_t r = (frame[i] & 0x00FF0000) >> 16;
		uint8_t g = (frame[i] & 0x0000FF00) >> 8;
		uint8_t b = frame[i] & 0x000000FF;
		led_set_true_color(i, r, g, b);
	}
}