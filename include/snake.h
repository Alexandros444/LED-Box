#ifndef SNAKE_H
#define SNAKE_H

#include "board.h"
#include "config.h"
#include "text.h"
#include <Arduino.h>

#include "colors.h"

bool is_point_inside_snake(Point pt);
void place_berry(void);
void init_snake();
void init_snake_game();
void step_snake();
void start_new_game();
int calc_auto_move_dir_from_pos(int x, int y);
void do_auto_move();
void step_snake_game();
void disp_snake_game();
void inc_game_speed();
void dec_game_speed();
void steer_snake(int dir);
void start_auto_move();
void stop_auto_move();


enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum cell_Flags {
	GROUND,
	BERRY
};

struct Snake{
	int len = 3;
	const int max_len = 256;
	Point body[256];
	int dir = RIGHT;
	bool has_won = false;
	bool has_lost = false;
};

struct Snake_Game{
	const long win_anim_dur_ms = 60000;
	const long loose_anim_dur_ms = 10000;
	bool is_anim_playing = false;
	long anim_start = 0;
	bool game_started = false;
	const long berry_timer = 5000;
	int berrys = 0;
	unsigned long last_berry_place = 0;
	unsigned long last_input_time = 0;
    unsigned long inactivity_timer = 120000;
	unsigned long sim_speed_ms = 1000;
	unsigned long last_sim_step_time = 0;
	bool auto_move = false;
};


static const char snake_loose_msg[] = "Haha du Looser!";
static const char snake_win_msg[] = "Gewonnen!";

#endif