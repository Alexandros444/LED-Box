#include "snake.h"

Snake_Game sgame;
Snake snake;

void inc_game_speed() {
	sgame.sim_speed_ms /= 2;
	set_sim_ms(sgame.sim_speed_ms);
}

void dec_game_speed() {
	sgame.sim_speed_ms = sgame.sim_speed_ms * 2 + 1;
	set_sim_ms(sgame.sim_speed_ms);
}

void steer_snake(int dir) {
	if (!sgame.game_started)
		return;
	snake.dir = dir;
	sgame.last_input_time = millis();
}

void clear_cells(void) {
	for (int x = 0; x < PIXELS_WIDTH; x++){
		for (int y = 0; y < PIXELS_HEIGHT; y++){
			cells[x][y] = 0;
		}
	}
}

bool is_point_inside_snake(Point pt){
	for (int i = 0; i < snake.len; i++){
		if (snake.body[i].x == pt.x && snake.body[i].y == pt.y)
			return true;
	}
	return false;
}

void place_berry(void){
	Point new_berry_place;
	new_berry_place.x = rand() % PIXELS_WIDTH;
	new_berry_place.y = rand() % PIXELS_HEIGHT;

	int tries = 5;
	
	while (is_point_inside_snake(new_berry_place) && tries > 0) {
		new_berry_place.x = rand() % PIXELS_WIDTH;
		new_berry_place.y = rand() % PIXELS_HEIGHT;
		Serial.print("Placed Berry in Snake");
		tries--;
	}

	// Place Berry at ok spot
	// bool found = false;
	// if (tries <= 0) {

	// 	bool checked_cells[PIXELS_WIDTH][PIXELS_HEIGHT] = { 1 };
	// 	for (int n = 0; n < snake.len; n++) {
	// 		checked_cells[snake.body[n].x][snake.body[n].y] = 0;
	// 	}

	// 	for (int x = 0; x < PIXELS_WIDTH; x++){
	// 		for (int y = 0; y < PIXELS_HEIGHT; y++){
	// 			if (checked_cells[x][y]) {
	// 				new_berry_place.x = x;
	// 				new_berry_place.y = y;
	// 				break;
	// 			}
	// 		}
	// 	}
		
		// for (int i = NUM_PIXELS - 1; i >= 0 && !found; i--) {
		// 	int x;
		// 	int y;
		// 	idx_to_pos(i, &x, &y);
		// 	for (int n = 0; n < snake.len; n++){
		// 		if (snake.body[n].x == x && snake.body[n].y == y)
		// 			continue;
		// 		new_berry_place.x = x;
		// 		new_berry_place.y = y;
		// 		found = true;
		// 		break;
		// 	}
		// }
		
	// }


	Serial.printf("Placed Berry x:%d, y:%d",new_berry_place.x,new_berry_place.y);
	cells[new_berry_place.x][new_berry_place.y] = BERRY;
	sgame.berrys++;
}

void init_snake(){
	snake.len = 4;
	snake.dir = RIGHT;
	snake.body[0].x = 3;
	snake.body[0].y = 2;
	snake.body[1].x = 2;
	snake.body[1].y = 2;
	snake.body[2].x = 1;
	snake.body[2].y = 2;
	snake.body[3].x = 0;
	snake.body[3].y = 2;
	snake.has_won = false;
	snake.has_lost = false;
}

void init_snake_game(){
	clear_cells();
	sgame.sim_speed_ms = 1000;
	sgame.is_anim_playing = false;
	sgame.game_started = true;
	sgame.berrys = 0;
	set_sim_ms(sgame.sim_speed_ms);
}

void step_snake(){
	Point head = snake.body[0];
	switch (snake.dir)	{
	case RIGHT:
		head.x++;
		break;
	case LEFT:
		head.x--;
		break;
	case UP:
		head.y--;
		break;
	case DOWN:
		head.y++;
		break;
	default:
		break;
	}

	if (head.x < 0 || head.y < 0 || head.x >= PIXELS_WIDTH || head.y >= PIXELS_HEIGHT || is_point_inside_snake(head)){
		snake.has_lost = true;
		return;
	}
	
	// Serial.printf("Snake Body: ");
	for (int i = snake.max_len-1; i >= 1; i--){
		snake.body[i] = snake.body[i-1];
		// Serial.printf("(%d,%d)",snake.body[i].x,snake.body[i].y);
	}
	// Serial.println();
	snake.body[0] = head;

	if (cells[head.x][head.y] == BERRY){
		snake.len++;
		sgame.berrys--;
		cells[head.x][head.y] = GROUND;
	}
	if (snake.len >= snake.max_len){
		snake.has_won = true;
		Serial.printf("SNAKE WON HOW %d >= %d",snake.len,snake.max_len);
	}

	Serial.printf("Head: x:%d y:%d\n\ridx:%d, dir:%d\n\rlen:%d, mxlen%d\n\r",head.x,head.y,pos_to_idx(head.x,head.y),snake.dir,snake.len,snake.max_len);

}

void start_new_game(){
	init_snake();
	init_snake_game();
}

int calc_auto_move_dir_from_pos(int x, int y) {
	// Upper Row
	if (y == 0) {
		if (x % 2 == 0)
			return RIGHT;
		else
			return DOWN;
	}
	// Pre Bottom Row
	if (y == PIXELS_HEIGHT - 2) {
		if (x % 2 == 0)
			return UP;
		if (x == PIXELS_WIDTH - 1)
			return DOWN;
		return RIGHT;
	}
	// Bottom Row
	if (y == PIXELS_HEIGHT - 1) {
		if (x == 0)
			return UP;
		return LEFT;
	}
	// Middle Rows
	if (x % 2 == 0) {
		return UP;
	}
	return DOWN;
}

void do_auto_move() {
	snake.dir = calc_auto_move_dir_from_pos(snake.body[0].x, snake.body[0].y);
}

void step_snake_game() {
	if (!sgame.game_started)
		start_new_game();

	if ((snake.has_won || snake.has_lost ) && !sgame.is_anim_playing){
		Serial.printf("Snake hast lost:%d won:%d\n Start animation.", snake.has_lost, snake.has_won);
		sgame.sim_speed_ms = 100;
		sgame.is_anim_playing = true;
		sgame.anim_start = millis();
	}
	bool win_anim_finished = (snake.has_won && millis() > sgame.win_anim_dur_ms + sgame.anim_start);
	bool loose_anim_finished = (snake.has_lost && millis() > sgame.loose_anim_dur_ms + sgame.anim_start);
	if (sgame.is_anim_playing && (win_anim_finished || loose_anim_finished)){
		start_new_game();
	}
	if (sgame.is_anim_playing) return;

	if (millis() > sgame.last_input_time + sgame.inactivity_timer) {
		do_auto_move();
	}

	step_snake();

	if ((sgame.berrys <= 0) || (millis() > sgame.last_berry_place + sgame.berry_timer)) {
		sgame.last_berry_place = millis();
		place_berry();
	}
}

void disp_snake_game(){

	for (int x = 0; x < PIXELS_WIDTH; x++){
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			byte n = pos_to_idx(x, y);
			if (cells[x][y] == BERRY)
				led_set_data(n, 1, 0, 0);
			else
				led_set_data(n, 0, 0, 0);
		}
	}

	// Serial.printf("Display Snake at: ");
	for (size_t i = 0; i < snake.len; i++){
		// Serial.printf("(%d,%d),",snake.body[i].x,snake.body[i].y);
		byte n = pos_to_idx(snake.body[i].x, snake.body[i].y);
		if (i == 0) led_set_data(n, 1, 0, 1);
		else led_set_data(n, 0, 1, 0);
	}
	// Serial.println();

	if (snake.has_lost) {
		scroll_disp_str("HAHA Du Looser!", false);
	}

	if (snake.has_won){
		scroll_disp_str("Gewonnen.", false);
	}
	
}