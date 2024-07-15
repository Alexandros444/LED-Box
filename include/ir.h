#ifndef IR_H
#define IR_H

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <Arduino.h>
#include "config.h"
#include "ir_codes.h"
#include "led.h"
#include "text.h"
#include "snake.h"
#include "cells.h"
#include "frames.h"

void ir_receive();
void receive_ir_code(uint32_t code);
void ir_begin();

#endif