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
uint8_t brightness = 1;
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
bool is_i_run = false;

byte cells[PIXELS_WIDTH][PIXELS_HEIGHT] = { 0 };
byte survival_rule[] = {1,2,3,4,5,6};
byte birth_rule[] = {1};

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

byte safe_cell_lookup(int x, int y) {
	if (x < 0 || y < 0 || x >= PIXELS_WIDTH || y >= PIXELS_HEIGHT) return 0;
	return cells[x][y];
}

void disp_cells(void) {
	for (int x = 0; x < PIXELS_WIDTH; x++) {
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			byte idx = pos_to_idx(x, y);
			ws2812b.setPixelColor(idx, ws2812b.Color(brightness * cells[x][y], brightness * cells[x][y], brightness * cells[x][y]));
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
	case Teal2_code:
		is_i_run = !is_i_run;
		break;
	case Orange_code:
		i_frame++;
		break;
	case Orange2_code:
		i_frame--;
		break;
	case R_code:
		frame_ms -= 10;
		break;
	case B_code:
		frame_ms += 100;
		break;
	case G_code:
		bounce = !bounce;
		break;
	case Flash_code:
		run_cells_step();
		break;
	case Strobe_code:
		random_splash(10);
		break;
	default:
		// Serial.print("Cant find Code: ");
		// Serial.println(code, HEX);
		break;
	}
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

	random_splash(20);
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
	if (millis() > last_frame + frame_ms){
		last_frame = millis();

		disp_cells();


		// display_frame(neo_color, neo_color_size);
// scroll_disp_str("Kalina!", false);
		Serial.printf("Scroll offset: %d\nScroll dir: %d\n",scroll_offset, scroll_dir);
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