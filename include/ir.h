#ifndef IR_H
#define IR_H

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "config.h"
#include "ir_codes.h"
#include "led.h"
#include "text.h"
#include "snake.h"
#include "cells.h"

IRrecv irrecv(RECV_PIN);
decode_results results;

void receive_ir_code(uint32_t code);

#endif