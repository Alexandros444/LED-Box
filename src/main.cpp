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

IRrecv irrecv(RECV_PIN);
decode_results results;

uint32_t* frames[] = { test_color, black_color, white_color, I_color, K_color, A_color };
size_t frame_sizes[] = { test_color_size, black_color_size, white_color_size, I_color_size, K_color_size, A_color_size };
int i_frame = 0;
bool is_i_run = false;

void display_char(int x_pos, char c);
void disp_str(String str, int offset);
void receive_ir_code(uint32_t code);

bool is_on = true;
uint8_t brightness = 0;
uint8_t max_bright = 150;
uint8_t step_bright = 1;

uint32_t last_ir_code = 0;
int ir_inc_dec = 1;

unsigned int frame_ms = 1000;
long last_frame = 0;

void setup() {
	Serial.begin(115200);

	irrecv.enableIRIn(); // Start the receiver

	ws2812b.begin();  // initialize WS2812B strip object (REQUIRED)
	// ws2812b.setBrightness(50);
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
	if (is_i_run && millis() > last_frame + frame_ms){
		last_frame = millis();
		i_frame++;
	} 
	if (i_frame > PIXELS_WIDTH) i_frame = - 6 * CHAR_WIDTH;
	if (!is_on)
		ws2812b.clear();
	// 	disp_str("Kalina", i_frame);
	// else 
	
	ws2812b.show();                                          // update to the WS2812B Led Strip
	return;
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
		scroll_disp_str("Kalina");
		break;
	case G_code:
		bounce = !bounce;
	default:
		// Serial.print("Cant find Code: ");
		// Serial.println(code, HEX);
		break;
	}
}

void display_char(int x_pos, char c) {

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
				uint32_t col = ws2812b.Color(brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx]);
				ws2812b.setPixelColor(px, col);
			}
			if (frame_idx % PIXELS_HEIGHT == 0)
				frame_idx += 2 * PIXELS_HEIGHT;
			frame_idx--;
		}
	} else {
		int frame_idx = 0;
		for (int px = x_start; px < NUM_PIXELS && frame_idx < frame_px_len; px++) {
			if (px >= 0) {
				uint32_t col = ws2812b.Color(brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx], brightness * disp_frame[frame_idx]);
				ws2812b.setPixelColor(px, col);
			}
			frame_idx++;
		}
	}
		

}

void disp_str(String str, int offset) {
	for (int i = 0; i < str.length(); i++) {
		display_char(i * CHAR_WIDTH + offset, str[i]);
	}
}

int scroll_offset = 0;
int scroll_distance = 0;
String scroll_string = "";
int scroll_width = 0;
int scroll_dir = 1;
bool bounce = false;

void set_scroll_disp_str(String str) {
	// Start at right
	scroll_string = str;
	scroll_width = str.length() * CHAR_WIDTH;
	scroll_offset = scroll_dir > 0 ? PIXELS_WIDTH : - scroll_width;
	// scroll_distance = PIXELS_WIDTH - str.length() * CHAR_WIDTH;
}

void scroll_disp_str(String str) {
	if (scroll_string != str) set_scroll_disp_str(str);
	disp_str(scroll_string, scroll_offset);
	scroll_offset -= scroll_dir;

	if (scroll_dir > 0 && scroll_offset + scroll_width < 0) {
		scroll_offset = PIXELS_WIDTH;
		if (bounce) scroll_dir = !scroll_dir;
	}
	else if (scroll_dir < 0 && scroll_offset > PIXELS_WIDTH) {
		scroll_offset = -scroll_width;
		if (bounce) scroll_dir = !scroll_dir;
	}
}


