#ifndef CELLS_H
#define CELLS_H

#include "board.h"
#include "config.h"
#include <Arduino.h>
#include "led.h"

void random_splash(int size);
void disp_cells(byte r, byte g, byte b);
void run_cells_step(void);

#endif