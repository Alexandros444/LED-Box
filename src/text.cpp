#include "text.h"

int scroll_offset = 0;
int scroll_distance = 0;
char *scroll_string = nullptr;
int scroll_n_chars = 0;
int scroll_width = 0;
int scroll_dir = 1;
bool bounce = true;
bool bounce_at_str_start = false;

// unsigned long last_scroll_step_time = 0;
unsigned long scroll_step_time_ms = 200;

void toggle_bounce() {
	bounce = !bounce;
}

void inc_scroll_speed() {
	scroll_step_time_ms /= 2;
}

void dec_scroll_speed() {
	scroll_step_time_ms = scroll_step_time_ms * 2 + 1;
}

void display_char(int x_pos, char c, bool removeBackground) {
	byte* disp_frame = char_to_led_data(c);
	if ((x_pos + CHAR_WIDTH <= 0) || (x_pos >= PIXELS_WIDTH)) return;

	// Start Position of Frame, Top Left if even, Bottom Left if uneven
	int x_start = x_pos * PIXELS_HEIGHT;
	// if (x_pos % 2)
	// 	x_start += PIXELS_HEIGHT - 1;

	// If x_pos < 0, or x_pos > x_len - frame_width

	if (x_pos % 2) {
		// Serial.printf("\nungerade,%d %d\n\n",x_start, x_pos);
		// Serial.printf("Ungerade Start: %d\n\r",x_start);
		int frame_idx = PIXELS_HEIGHT -1;
		for (int px = x_start; px < NUM_PIXELS && frame_idx < CHAR_N; px++) {
			// Serial.printf("px %d, fidx %d\n",px,frame_idx);
			if (px >= 0) {
				byte val = disp_frame[frame_idx];
				if ((val != 0) || removeBackground) {
					// Serial.printf("Frame idx:%d, data:%d, background:%d\n", frame_idx, disp_frame[frame_idx],removeBackground);
					led_set_data(px, val, val, val);
				}
			}
			if (frame_idx % PIXELS_HEIGHT == 0)
				frame_idx += 2 * PIXELS_HEIGHT;
			frame_idx--;
		}
	} else {
		// Serial.printf("Gerade Start: %d, bis %d\n\r",x_start, );
		int frame_idx = 0;
		for (int px = x_start; px < NUM_PIXELS && frame_idx < CHAR_N; px++) {
			if (px >= 0) {
				byte val = disp_frame[frame_idx];
				if ((val != 0) || removeBackground) {
					// Serial.printf(",ger: %d",px);
					// Serial.printf("Frame idx:%d, data:%d, background:%d\n", frame_idx, disp_frame[frame_idx],removeBackground);
					led_set_data(px, val, val, val);
				}
			}
			frame_idx++;
		}
	}
		

}

void disp_str(const char str[], int offset, bool remove_background) {
	for (int i = 0; i < scroll_width; i++) {
		// tick();
		// Serial.printf("\n\r%d Len, Displaying char %c\n\r",scroll_width, str[i]);
		display_char(i * CHAR_WIDTH + offset, str[i], remove_background);
		// delay(1000);
		// tock("Disp Char");
	}
}

void set_scroll_disp_str(const char str[]) {
	// Start at right
	scroll_string = (char*) str;
	scroll_width = strlen(str);
	Serial.printf("Setting New String %s\n\rMemory addr: %p, String Length: %d\n", str,&str,scroll_width);
	// scroll_width = scroll_n_chars * CHAR_WIDTH;
	scroll_offset = scroll_dir > 0 ? -scroll_width : PIXELS_WIDTH;
	// scroll_distance = PIXELS_WIDTH - str.length() * CHAR_WIDTH;
}

void scroll_disp_str(const char str[], bool remove_background) {
	static unsigned long last_scroll_step_time = 0;
	if (scroll_string != str) set_scroll_disp_str(str);
	else if (millis() < last_scroll_step_time + scroll_step_time_ms) {
		disp_str(str, scroll_offset, remove_background);	
		return;
	}
	last_scroll_step_time = millis();
	disp_str(str, scroll_offset, remove_background);
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


