#include "board.h"

int pos_to_idx(int x, int y) {
    int n_row = x * PIXELS_HEIGHT;
	int up_row = x % 2;
	int n = 0;
	if (up_row) n = n_row + PIXELS_HEIGHT - 1 - y;
	else n = n_row + y;
	return n;
}

void idx_to_pos(int n, int* x_ret, int* y_ret) {
	int row = n / PIXELS_HEIGHT;
	int up_row = row % 2;

	int x = row;
	int y = n % PIXELS_HEIGHT;
	if (up_row) y = PIXELS_HEIGHT - 1 - y;

	*x_ret = x;
	*y_ret = y;
}

void clear_cells(void){
	for (int x = 0; x < PIXELS_WIDTH; x++){
		for (int y = 0; y < PIXELS_HEIGHT; y++){
			cells[x][y] = 0;
		}
	}
}


int test_x = 0;
int test_y = 0;
void test_pos_to_idx_etc(){

	int n = pos_to_idx(test_x,test_y);
	led_set_data(n, 1, 1, 1);
	test_y++;
	if (test_y % PIXELS_HEIGHT == 0){
		test_y = 0;
		test_x++;
	}
	if (test_x % PIXELS_WIDTH == 0){
		test_x = 0;
	}
}


byte test_n = 0;
void test_idx_to_pos_etc(){
	int x;
	int y;
	idx_to_pos(test_n, &x, &y);
	led_set_data(pos_to_idx(x, y), 1, 1, 1);
	test_n++;
}


