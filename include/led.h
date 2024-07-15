#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

bool is_on = true;
uint8_t brightness = 5;
uint8_t max_bright = 150;
uint8_t step_bright = 15;
bool is_i_run = true;

#endif