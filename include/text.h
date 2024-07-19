#ifndef _TEXT_H
#define _TEXT_H

#include <Arduino.h>
#include "led.h"
#include "config.h"
#include "table.h"
#include "timing.h"

bool scroll_disp_str(const char str[], bool remove_background, int n_bounces);
void toggle_bounce();
void inc_scroll_speed();
void dec_scroll_speed();
void scroll_disp_force_new_str(const char str[], int n_bounces);

#endif