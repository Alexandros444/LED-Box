#ifndef SCENES_H
#define SCENES_H

#include "text.h"
#include "snake.h"
#include "cells.h"
#include "web.h"
#include "ir_codes.h"
#include "frames.h"

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

inline int current_scene = WEB;
inline const int num_scenes = 5;


#endif