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
#include "led_matrix_color_data.h"
#include "table.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define PIN_WS2812B 21  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 256   // The number of LEDs (pixels) on WS2812B LED strip
#define PIXELS_HEIGHT 8
#define PIXELS_WIDTH 32


Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

#define RECV_PIN 19

IRrecv irrecv(RECV_PIN);

decode_results results;


uint32_t* frames[] = { test_color, black_color, white_color, I_color, K_color, A_color };
size_t frame_sizes[] = { test_color_size, black_color_size, white_color_size, I_color_size, K_color_size, A_color_size };
int i_frame = 0;

void display_char(int x_pos, char c);

void setup() {
	Serial.begin(115200);

	irrecv.enableIRIn(); // Start the receiver

	ws2812b.begin();  // initialize WS2812B strip object (REQUIRED)
	ws2812b.setBrightness(50);
}

uint32_t last_ir_code = 0;
int ir_inc_dec = 1;

void loop() {

	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		if (results.value != last_ir_code){
			last_ir_code = results.value;
			ir_inc_dec = -ir_inc_dec;
		}
		irrecv.resume(); // Receive the next value
		i_frame = i_frame + ir_inc_dec;//(i_frame + 1) % (sizeof(frames) / sizeof(uint32_t*));
		if (i_frame > 40) i_frame = -10;
	}

	// ws2812b.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

	// uint32_t* frame = frames[i_frame];
	// size_t frame_len = frame_sizes[i_frame];

	// // turn pixels to green one-by-one with delay between each pixel
	// for (int pixel = 0; pixel < NUM_PIXELS && pixel < frame_len; pixel++) {         // for each pixel
	// 	ws2812b.setPixelColor(pixel, frame[pixel]);  // it only takes effect if pixels.show() is called

	// 	// delay(5);  // 500ms pause between each pixel
	// }

	display_char(i_frame, 'K');

	ws2812b.show();                                          // update to the WS2812B Led Strip
	return;
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
				uint32_t col = ws2812b.Color(255 * disp_frame[frame_idx], 255 * disp_frame[frame_idx], 255 * disp_frame[frame_idx]);
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
				uint32_t col = ws2812b.Color(255 * disp_frame[frame_idx], 255 * disp_frame[frame_idx], 255 * disp_frame[frame_idx]);
				ws2812b.setPixelColor(px, col);
			}
			frame_idx++;
		}
	}
		

}

