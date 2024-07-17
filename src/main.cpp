#include <Arduino.h>

// #include "ir.h"
// #include "scenes.h"
// #include "timing.h"
// #include "board.h"

#include "led.h"
#include "board.h"
#include "config.h"
#include "ir.h"
#include "scenes.h"
#include "timing.h"

void setup() {
	Serial.begin(115200);

	// Start the receiver
	ir_begin();
	led_begin();  // initialize WS2812B strip object (REQUIRED)
	// ws2812b.setBrightness(50);

	// random_splash(50);
	led_clear();
	start_new_scene();
	// ws2812b.begin();
}

// unsigned long time_stamp1 = 0;
// unsigned long time_stamp2 = 0;


void loop() {
	// tick();
	// tick();
	ir_receive();
	// tockTick("IR");
	// scroll_disp_str("Kalin", true);
	run_scene();
	// tockTick("RUN");
	disp_scene();
	// tockTick("DISP");
	led_show();
	// tock("LED");
	// tock("Full Loop");

	// ws2812b.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

	// uint32_t* frame = frames[i_frame];
	// size_t frame_len = frame_sizes[i_frame];

	// // turn pixels to green one-by-one with delay between each pixel
	// for (int pixel = 0; pixel < NUM_PIXELS && pixel < frame_len; pixel++) {         // for each pixel
	// 	ws2812b.setPixelColor(pixel, frame[pixel]);  // it only takes effect if pixels.show() is called

	
	// 	// delay(5);  // 500ms pause between each pixel
	// }

	// run_scene();
	// test_pos_to_idx_etc();
	
	// if (is_new_frame_time()) {
		// disp_cells(1,0,0);
		// test_pos_to_idx_etc();
		// display_frame(acid_color, acid_color_size);
		// test_idx_to_pos_etc();

		// scroll_disp_str(" ",false);
		// time_stamp1 = micros();
		// Serial.printf("Step snake time: %ld\n\r", micros() - time_stamp1);
		// run_cells_step();

		// time_stamp1 = micros();
		// Serial.printf("Disp snake time: %ld\n\r", micros() - time_stamp1);

		// scroll_disp_str("Kalina!", false);
		// Serial.printf("Scroll offset: %d\nScroll dir: %d\n",scroll_offset, scroll_dir);
		// pixel_lim++;
	// } 
	// led_show();                                     // update to the WS2812B Led Strip

	// if (i_frame > PIXELS_WIDTH) i_frame = - 6 * CHAR_WIDTH;
	// 	disp_str("Kalina", i_frame);
	// else 
}



	// GOOD EFFEKT
	// for (int i = 0; i < pixel_lim; i++){
	// 	ws2812b.setPixelColor(i,0x00000000);
	// }