#ifndef CELLS_H
#define CELLS_H

#include "board.h"
#include "config.h"
#include <Arduino.h>
#include "led.h"

byte survival_rule[] = {2,3};
byte birth_rule[] = {3,4};

void random_splash(int size);

#endif