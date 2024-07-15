#include "ir.h"

IRrecv irrecv(RECV_PIN);
decode_results results;

void ir_begin() {
	irrecv.enableIRIn(); 
}

void ir_receive() {
	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		irrecv.resume(); // Receive the next value
		receive_ir_code(results.value);
	}
}

void receive_ir_code(uint32_t code) {
	uint8_t newBrightness;
	switch (code){
	case Off_code:
		turn_disp_off();
		break;
	case On_code:
		turn_disp_on();
		break;
	case bright_code:
		inc_brightness();
		break;
	case dim_code:
		dec_brightness();
		break;
	case Flash_code:
		toggle_frames();
		break;
	case R_code:
		inc_game_speed();
		break;
	case B_code:
		dec_game_speed();
		break;
	case G_code:
		toggle_bounce();
		break;
	case Green_code:
		steer_snake(UP);
		break;
	case Purple_code:
		steer_snake(RIGHT);
		break;
	case Teal2_code:
		steer_snake(DOWN);
		break;
	case Orange2_code:
		steer_snake(LEFT);
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