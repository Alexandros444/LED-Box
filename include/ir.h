#ifndef IR_H
#define IR_H

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <Arduino.h>
#include "config.h"
#include "ir_codes.h"
#include "scenes.h"

void ir_receive();
void ir_begin();

#endif