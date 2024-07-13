/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ws2812b-led-strip
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "led_matrix_data.h"
#include "led_matrix_color_data.h"
// #include "table.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define PIN_WS2812B 21  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 256   // The number of LEDs (pixels) on WS2812B LED strip

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

#define RECV_PIN 19

IRrecv irrecv(RECV_PIN);

decode_results results;


uint32_t* frames[] = { test_color, black_color, white_color, i_color, K_color, A_color };
size_t frame_sizes[] = { test_color_size, black_color_size, white_color_size, i_color_size, K_color_size, A_color_size };
int i_frame = 0;

void setup() {
	Serial.begin(115200);

	irrecv.enableIRIn(); // Start the receiver

	ws2812b.begin();  // initialize WS2812B strip object (REQUIRED)
	ws2812b.setBrightness(128);
}

void loop() {

	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		irrecv.resume(); // Receive the next value
		i_frame = (i_frame + 1) % (sizeof(frames) / sizeof(uint32_t*));
	}

	// ws2812b.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

	uint32_t* frame = frames[i_frame];
	size_t frame_len = frame_sizes[i_frame];

	// turn pixels to green one-by-one with delay between each pixel
	for (int pixel = 0; pixel < NUM_PIXELS && pixel < frame_len; pixel++) {         // for each pixel
		ws2812b.setPixelColor(pixel, frame[pixel]);  // it only takes effect if pixels.show() is called

		// delay(5);  // 500ms pause between each pixel
	}
	ws2812b.show();                                          // update to the WS2812B Led Strip

	// turn off all pixels for two seconds
	// ws2812b.clear();
	// ws2812b.show();  // update to the WS2812B Led Strip
	return;
	delay(2000);     // 2 seconds off time

	// turn on all pixels to red at the same time for two seconds
	for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
		ws2812b.setPixelColor(pixel, ws2812b.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
	}
	ws2812b.show();  // update to the WS2812B Led Strip
	delay(1000);     // 1 second on time

	// turn off all pixels for one seconds
	ws2812b.clear();
	ws2812b.show();  // update to the WS2812B Led Strip
	delay(1000);     // 1 second off time
}