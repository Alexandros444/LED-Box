#include "frames.h"

void display_frame(uint32_t* frame, int len) {
	// float brightness_scale = ((float)brightness) / 255;
	for (int i = 0; i < NUM_PIXELS && i < len; i++) {
		uint8_t r = (frame[i] & 0x00FF0000) >> 16;
		uint8_t g = (frame[i] & 0x0000FF00) >> 8;
		uint8_t b = frame[i] & 0x000000FF;
		r = r * brightness / 255;
		g = g * brightness / 255;
		b = b * brightness / 255;
		uint32_t color = 0x00000000 | (r << 16) | (g << 8) | b;
		ws2812b.setPixelColor(i, color);
	}
}