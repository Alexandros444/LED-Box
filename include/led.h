#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

void led_begin();
void led_clear();
void led_show();
void turn_disp_off();
void turn_disp_on();
void inc_brightness();
void dec_brightness();
byte get_brightness();
void led_set_true_color(byte n, byte r, byte g, byte b);
void led_set_data(byte n, byte r, byte g, byte b);

#endif