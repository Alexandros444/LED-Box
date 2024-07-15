/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ws2812b-led-strip
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
 // #include "led_matrix_data.h"
#include "ir_codes.h"
#include "led_matrix_color_data.h"
#include "table.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define RECV_PIN 19
#define PIN_WS2812B 21  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 256   // The number of LEDs (pixels) on WS2812B LED strip
#define PIXELS_HEIGHT 8
#define PIXELS_WIDTH 32
#define CHAR_WIDTH 5
#define MAX_CHARS PIXELS_WIDTH / CHAR_WIDTH

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

bool is_on = true;
uint8_t brightness = 100;
uint8_t max_bright = 150;
uint8_t step_bright = 1;

uint32_t last_ir_code = 0;
int ir_inc_dec = 1;

unsigned int frame_ms = 100;
long last_frame = 0;

int scroll_offset = 0;
int scroll_distance = 0;
String scroll_string = "";
int scroll_width = 0;
int scroll_dir = 1;
bool bounce = true;
bool bounce_at_str_start = true;

byte dead_pixels[] = { 174 };
byte pixel_lim = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

uint32_t* frames[] = { test_color, black_color, white_color, I_color, K_color, A_color };
size_t frame_sizes[] = { test_color_size, black_color_size, white_color_size, I_color_size, K_color_size, A_color_size };
int i_frame = 0;
bool is_i_run = true;

byte cells[PIXELS_WIDTH][PIXELS_HEIGHT] = { 0 };
byte survival_rule[] = {2,3};
byte birth_rule[] = {3,4};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum cell_Flags {
	GROUND,
	SNAKE,
	BERRY
}; 

struct Point{
	int x;
	int y;
}typedef Point;

struct Snake{
	int len = 3;
	const int max_len = 32;
	Point body[32];
	int dir = RIGHT;
	bool has_won = false;
	bool has_eaten_berry = true;
	bool has_lost = false;
};

struct Snake_Game{
	int speed_ms = 100;
	const long win_anim_dur_ms = 60000;
	const long loose_anim_dur_ms = 10000;
	bool is_anim_playing = false;
	long anim_start = 0;
	bool game_started = false;
};

Snake_Game sgame;
Snake snake;

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


void display_char(int x_pos, char c, bool removeBackground) {
	byte* disp_frame = char_to_led_data(c);
	int frame_px_len = sizeof(A) / sizeof(A[0]); // Assume Every Char has the Same Size
	int frame_width = frame_px_len / PIXELS_HEIGHT;
	if (x_pos + frame_width <= 0 || x_pos >= PIXELS_WIDTH) return;

	// Start Position of Frame, Top Left if even, Bottom Left if uneven
	int x_start = x_pos * PIXELS_HEIGHT;
	// if (x_pos % 2)
	// 	x_start += PIXELS_HEIGHT - 1;

	// If x_pos < 0, or x_pos > x_len - frame_width

	if (x_pos % 2) {
		// Serial.printf("\nungerade,%d %d\n\n",x_start, x_pos);
		int frame_idx = PIXELS_HEIGHT -1;
		for (int px = x_start; px < NUM_PIXELS && frame_idx < frame_px_len; px++) {
			// Serial.printf("px %d, fidx %d\n",px,frame_idx);
			if (px >= 0) {
				if (disp_frame[frame_idx] != 0 || removeBackground){
					uint32_t col = ws2812b.Color(brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx]);
					ws2812b.setPixelColor(px, col);
				}
			}
			if (frame_idx % PIXELS_HEIGHT == 0)
				frame_idx += 2 * PIXELS_HEIGHT;
			frame_idx--;
		}
	} else {
		int frame_idx = 0;
		for (int px = x_start; px < NUM_PIXELS && frame_idx < frame_px_len; px++) {
			if (px >= 0) {
				if (disp_frame[frame_idx] != 0 || removeBackground){
					uint32_t col = ws2812b.Color(brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx]);
					ws2812b.setPixelColor(px, col);
				}
			}
			frame_idx++;
		}
	}
		

}

void disp_str(String str, int offset, bool remove_background) {
	for (int i = 0; i < str.length(); i++) {
		display_char(i * CHAR_WIDTH + offset, str[i], remove_background);
	}
}

void set_scroll_disp_str(String str) {
	// Start at right
	scroll_string = str;
	scroll_width = str.length() * CHAR_WIDTH;
	scroll_offset = scroll_dir > 0 ? -scroll_width : PIXELS_WIDTH;
	// scroll_distance = PIXELS_WIDTH - str.length() * CHAR_WIDTH;
}

void scroll_disp_str(String str, bool remove_background) {
	if (scroll_string != str) set_scroll_disp_str(str);
	disp_str(scroll_string, scroll_offset, remove_background);
	scroll_offset += scroll_dir;

	bool str_end_out_right = scroll_offset + scroll_width > PIXELS_WIDTH;
	bool str_at_right_edge = scroll_offset + scroll_width >= PIXELS_WIDTH;
	bool str_out_right = scroll_offset >= PIXELS_WIDTH;

	bool str_start_out_left = scroll_offset < 0;
	bool str_at_left_edge = scroll_offset < 0;
	bool str_out_left = scroll_offset + scroll_width < 0;

	bool scroll_left = scroll_dir < 0;
	bool scroll_right = scroll_dir > 0;

	if (scroll_width > PIXELS_WIDTH){
		str_at_right_edge = scroll_offset >= 0;
		str_at_left_edge = scroll_offset + scroll_width <= PIXELS_WIDTH;
	}


	if (bounce && bounce_at_str_start && (scroll_left && str_at_left_edge || scroll_right && str_at_right_edge)){
		scroll_dir = -scroll_dir;
		return;
	}

	if (scroll_left && str_out_left) {
		if (bounce) scroll_dir = -scroll_dir;
		else scroll_offset = PIXELS_WIDTH;
	}
	else if (scroll_right && str_out_right) {
		if (bounce) scroll_dir = -scroll_dir;
		else scroll_offset = -scroll_width;
	}
}



void clear_cells(void){
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
	
	while (is_point_inside_snake(new_berry_place)){
		new_berry_place.x = rand() % PIXELS_WIDTH;
		new_berry_place.y = rand() % PIXELS_HEIGHT;
		Serial.print("Placed Berry in Snake");
	}
	
	Serial.printf("Placed Berry x:%d, y:%d",new_berry_place.x,new_berry_place.y);
	cells[new_berry_place.x][new_berry_place.y] = BERRY;

}

void init_snake(){
	snake.len = 3;
	snake.dir = RIGHT;
	snake.body[0].x = 3;
	snake.body[0].y = 2;
	snake.body[1].x = 2;
	snake.body[1].y = 2;
	snake.body[2].x = 1;
	snake.body[2].y = 2;	
	snake.has_won = false;
	snake.has_eaten_berry = true;
	snake.has_lost = false;
}

void init_snake_game(){
	clear_cells();
	sgame.is_anim_playing = false;
	sgame.speed_ms = 100;
	sgame.game_started = true;
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
	
	Serial.printf("Snake Body: ");
	for (int i = 0; i < snake.max_len-1; i++){
		snake.body[i+1] = snake.body[i];
		Serial.printf("(%d,%d)",snake.body[i].x,snake.body[i].y);
	}
	Serial.println();
	snake.body[0] = head;

	if (cells[head.x][head.y] == BERRY){
		snake.len++;
		snake.has_eaten_berry = true;
	}
	if (snake.len >= snake.max_len){
		snake.has_won = true;
		Serial.printf("SNAKE WON HOW %d >= %d",snake.len,snake.max_len);
	}

	Serial.printf("Head: x:%d y:%d\nidx:%d, dir:%d\nlen:%d, mxlen%d\n",head.x,head.y,pos_to_idx(head.x,head.y),snake.dir,snake.len,snake.max_len);


}

void start_new_game(){
	init_snake();
	init_snake_game();
}

void step_snake_game(){
	if (!sgame.game_started)
		start_new_game();

	if ((snake.has_won || snake.has_lost ) && !sgame.is_anim_playing){
		Serial.printf("Snake hast lost:%d won:%d\n Start animation.",snake.has_lost,snake.has_won);
		sgame.is_anim_playing = true;
		sgame.anim_start = millis();
	}
	bool win_anim_finished = (snake.has_won && millis() > sgame.win_anim_dur_ms + sgame.anim_start);
	bool loose_anim_finished = (snake.has_lost && millis() > sgame.loose_anim_dur_ms + sgame.anim_start);
	if (sgame.is_anim_playing && (win_anim_finished || loose_anim_finished)){
		start_new_game();
	}
	if (sgame.is_anim_playing) return;

	step_snake();

	if (snake.has_eaten_berry){
		clear_cells();
		place_berry();
		snake.has_eaten_berry = false;
	}
}

void disp_snake_game(){

	for (int x = 0; x < PIXELS_WIDTH; x++){
		for (int y = 0; y < PIXELS_HEIGHT; y++){
			byte n = pos_to_idx(x,y);
			if(cells[x][y] == BERRY)
				ws2812b.setPixelColor(n,ws2812b.Color(brightness, 0,0));
			else
			 	ws2812b.setPixelColor(n,0x00);
		}
	}

	for (size_t i = 0; i < snake.len; i++){
		byte n = pos_to_idx(snake.body[i].x,snake.body[i].y);
		ws2812b.setPixelColor(n,ws2812b.Color(0,brightness,0));
	}

	if (snake.has_lost){
		scroll_disp_str("HAHA Du Noob!", false);
	}

	if (snake.has_won){
		scroll_disp_str("Gewonnen.", false);
	}
	
}

byte safe_cell_lookup(int x, int y) {
	if (x < 0 || y < 0 || x >= PIXELS_WIDTH || y >= PIXELS_HEIGHT) return 0;
	return cells[x][y];
}

void disp_cells(byte r, byte g, byte b) {
	for (int x = 0; x < PIXELS_WIDTH; x++) {
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			byte idx = pos_to_idx(x, y);
			ws2812b.setPixelColor(idx, ws2812b.Color(brightness * cells[x][y] * r, brightness * cells[x][y] * g, brightness * cells[x][y] * b));
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

void receive_ir_code(uint32_t code) {
	uint8_t newBrightness;
	switch (code){
	case Off_code:
		is_on = false;
		break;
	case On_code:
		is_on = true;
		break;
	case bright_code:
		brightness += step_bright;
		if (brightness > max_bright)brightness = max_bright;
		Serial.print(brightness);
		break;
	case dim_code:
		newBrightness = brightness - step_bright;
		if (brightness < newBrightness) brightness = 0;
		else brightness = newBrightness;
		Serial.print(brightness);
		break;
	case Flash_code:
		is_i_run = !is_i_run;
		break;
	case Orange_code:
		i_frame++;
		break;
	case Orange2_code:
		i_frame--;
		break;
	case R_code:
		sgame.speed_ms -= 20;
		break;
	case B_code:
		sgame.speed_ms += 100;
		break;
	case G_code:
		bounce = !bounce;
		break;
	case Strobe_code:
		random_splash(30);
		break;
	case Fade_code:
		clear_cells();
		break;
		
	default:
		// Serial.print("Cant find Code: ");
		// Serial.println(code, HEX);
		break;
	}
}

void display_frame(uint32_t* frame, int len) {
	// float brightness_scale = ((float)brightness) / 255;
	for (int i = 0; i < NUM_PIXELS && i < len; i++) {
		uint8_t r = (frame[i] & 0x00FF0000) >> 16;
		uint8_t g = (frame[i] & 0x0000FF00) >> 8;
		uint8_t b = frame[i] & 0x000000FF;
		r = r * brightness / 255;
		g = g * brightness / 255;
		b = b * brightness / 255;
		uint32_t color = 0x00000000 | (r << 16) | (g << 8) | b;
		ws2812b.setPixelColor(i, color);
	}
}








void setup() {
	Serial.begin(115200);

	irrecv.enableIRIn(); // Start the receiver

	ws2812b.begin();  // initialize WS2812B strip object (REQUIRED)
	// ws2812b.setBrightness(50);

	random_splash(50);
}

void loop() {

	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		irrecv.resume(); // Receive the next value
		receive_ir_code(results.value);
	}

	// ws2812b.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

	// uint32_t* frame = frames[i_frame];
	// size_t frame_len = frame_sizes[i_frame];

	// // turn pixels to green one-by-one with delay between each pixel
	// for (int pixel = 0; pixel < NUM_PIXELS && pixel < frame_len; pixel++) {         // for each pixel
	// 	ws2812b.setPixelColor(pixel, frame[pixel]);  // it only takes effect if pixels.show() is called

	
	// 	// delay(5);  // 500ms pause between each pixel
	// }

	if (millis() > last_frame + sgame.speed_ms){
		last_frame = millis();
		// disp_cells(1,0,0);

		disp_snake_game();	

		if (is_i_run)
		{
			step_snake_game();
			// run_cells_step();
		}
		

		// display_frame(neo_color, neo_color_size);
		// scroll_disp_str("Kalina!", false);
		// Serial.printf("Scroll offset: %d\nScroll dir: %d\n",scroll_offset, scroll_dir);
		// pixel_lim++;
	} 

	// if (i_frame > PIXELS_WIDTH) i_frame = - 6 * CHAR_WIDTH;
	if (!is_on)
		ws2812b.clear();
	// 	disp_str("Kalina", i_frame);
	// else 
	


	ws2812b.show();                                          // update to the WS2812B Led Strip
}



	// GOOD EFFEKT
	// for (int i = 0; i < pixel_lim; i++){
	// 	ws2812b.setPixelColor(i,0x00000000);
	// }