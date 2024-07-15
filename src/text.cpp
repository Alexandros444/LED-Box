#include "text.h"

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
				if ((disp_frame[frame_idx] != 0) || removeBackground) {
					Serial.printf("Frame idx:%d, data:%d, background:%d\n", frame_idx, disp_frame[frame_idx],removeBackground);
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
				if ((disp_frame[frame_idx] != 0) || removeBackground) {
					Serial.printf("Frame idx:%d, data:%d, background:%d\n", frame_idx, disp_frame[frame_idx],removeBackground);
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


