#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "led.h"
#include "config.h"
#include "table.h"

int scroll_offset = 0;
int scroll_distance = 0;
String scroll_string = "";
int scroll_width = 0;
int scroll_dir = -1;
bool bounce = true;
bool bounce_at_str_start = true;

void set_scroll_disp_str(String str);
void scroll_disp_str(String str, bool remove_background);

#endif