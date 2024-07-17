#ifndef SCENES_H
#define SCENES_H

#include "text.h"
#include "snake.h"
#include "cells.h"
#include "web.h"
#include "ir_codes.h"
#include "frames.h"
#include "timing.h"
#include "messages.h"

enum SCENES {
    KALINA,
    SNAKE,
    CELL,
    ANIM,
    WEB,
};

void switch_scene();
void run_scene();
void disp_scene();
void start_new_scene();
void scene_handle_input(uint32_t val);

extern int current_scene;
extern const int num_scenes;

#endif