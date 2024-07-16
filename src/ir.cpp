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
		scene_handle_input(results.value);
		// receive_ir_code(results.value);
	}
}