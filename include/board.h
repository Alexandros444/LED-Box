#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include "config.h"
#include "led.h"

struct Point {
    int x;
	int y;
}typedef Point;

inline byte cells[PIXELS_WIDTH][PIXELS_HEIGHT];

int pos_to_idx(int x, int y);
void idx_to_pos(int n, int* x_ret, int* y_ret);
void clear_cells(void);

#endif