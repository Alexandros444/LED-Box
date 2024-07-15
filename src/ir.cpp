#include "ir.h"

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
		if (brightness < 100) step_bright = 25;
		if (brightness < 40) step_bright = 5;
		if (brightness < 10) step_bright = 1;
		Serial.print(brightness);
		break;
	case dim_code:
		newBrightness = brightness - step_bright;
		if (brightness < newBrightness) brightness = 0;
		else brightness = newBrightness;
		if (brightness < 100) step_bright = 25;
		if (brightness < 40) step_bright = 5;
		if (brightness < 10) step_bright = 1;
		Serial.print(brightness);
		break;
	case Flash_code:
		is_i_run = !is_i_run;
		break;
	case R_code:
		sim_ms /= 2;
		break;
	case B_code:
		sim_ms = sim_ms * 2 + 1;
		break;
	case G_code:
		bounce = !bounce;
		break;
	case Green_code:
		if (sgame.game_started) {
			snake.dir = UP;
			sgame.last_input_time = millis();
		}
		break;
	case Purple_code:
		if (sgame.game_started){
			snake.dir = RIGHT;
			sgame.last_input_time = millis();
		}
		break;
	case Teal2_code:
		if (sgame.game_started){
			snake.dir = DOWN;
			sgame.last_input_time = millis();
		}
		break;
	case Orange2_code:
		if (sgame.game_started){
			snake.dir = LEFT;
			sgame.last_input_time = millis();
		}
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