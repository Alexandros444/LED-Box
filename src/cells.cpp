#include "cells.h"

byte survival_rule[] = {2,3};
byte birth_rule[] = {3};

unsigned long last_cell_step_time = 0;
unsigned long cell_step_time_ms = 200;

void inc_cell_speed() {
	cell_step_time_ms /= 2;
}

void dec_cell_speed() {
	cell_step_time_ms = cell_step_time_ms * 2 + 1;
}

byte safe_cell_lookup(int x, int y) {
	if (x < 0 || y < 0 || x >= PIXELS_WIDTH || y >= PIXELS_HEIGHT) return 0;
	return cells[x][y];
}

void disp_cells(byte r, byte g, byte b) {
	for (int x = 0; x < PIXELS_WIDTH; x++) {
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			byte idx = pos_to_idx(x, y);
			led_set_scaled_color(idx, cells[x][y] * disp_color[0], cells[x][y] * disp_color[1], cells[x][y] * disp_color[0]);
		}
	}
} 

bool check_cell_become_alive(int alive_neighbours) {
	for (int i = 0; i < sizeof(birth_rule); i++) {
		if (alive_neighbours == birth_rule[i])
			return true;
	}
	return false;
}

bool check_cell_stay_alive(int alive_neighbours) {
	for (int i = 0; i < sizeof(survival_rule); i++) {
		if (alive_neighbours == survival_rule[i])
			return true;
	}
	return false;
}

int n_cell_neighbours(int x, int y) {
	byte n0 = safe_cell_lookup(x-1,y-1)	& 0x01;
	byte n1 = safe_cell_lookup(x,y-1) 	& 0x01;
	byte n2 = safe_cell_lookup(x+1,y-1) & 0x01;
	byte n3 = safe_cell_lookup(x-1,y) 	& 0x01;
	byte n5 = safe_cell_lookup(x+1,y) 	& 0x01;
	byte n6 = safe_cell_lookup(x-1,y+1) & 0x01;
	byte n7 = safe_cell_lookup(x,y+1) 	& 0x01;
	byte n8 = safe_cell_lookup(x+1,y+1) & 0x01;
	return n0 + n1 + n2 + n3 + n5 + n6 + n7 + n8;
}

void run_cells_step(void) {
	if (millis() < last_cell_step_time + cell_step_time_ms)
		return;
	last_cell_step_time = millis();
	for (int x = 0; x < PIXELS_WIDTH; x++) {
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			int alive_neighbours = n_cell_neighbours(x, y);
			bool stays_alive = check_cell_stay_alive(alive_neighbours);
			bool becomes_alive = check_cell_become_alive(alive_neighbours);
			bool is_alive = (bool) cells[x][y];

			cells[x][y] = is_alive ? stays_alive : becomes_alive;

		}
	}
}

void random_splash(int size) {
	int num_splashes = rand() % (size);
	for (int i = 0; i < num_splashes; i++){
		byte splash_x = rand() % (PIXELS_WIDTH);
		byte splash_y = rand() % (PIXELS_HEIGHT);
		cells[splash_x][splash_y] = 0x1;
	}
	
}

byte cell_neighbours(int x, int y) {
	byte n0 = safe_cell_lookup(x-1,y-1);
	byte n1 = safe_cell_lookup(x,y-1);
	byte n2 = safe_cell_lookup(x+1,y-1);
	byte n3 = safe_cell_lookup(x-1,y);
	// byte n4 = safe_cell_lookup(x,y);
	byte n5 = safe_cell_lookup(x+1,y);
	byte n6 = safe_cell_lookup(x-1,y+1);
	byte n7 = safe_cell_lookup(x,y+1);
	byte n8 = safe_cell_lookup(x+1,y+1);
	return n0 | n1 | n2 | n3 | n5 | n6 | n7 | n8;
}