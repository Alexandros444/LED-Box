#ifndef _TEXT_H
#define _TEXT_H

#include <Arduino.h>
#include "led.h"
#include "config.h"
#include "table.h"

void set_scroll_disp_str(String str);
void scroll_disp_str(String str, bool remove_background);
void toggle_bounce();

#endif