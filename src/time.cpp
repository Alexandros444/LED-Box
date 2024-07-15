#include "time.h"

unsigned long frame_ms = 32;
unsigned long sim_ms = 100;
unsigned long last_frame = 0;
unsigned long last_sim = 0;

bool is_new_frame_time() {
    if (millis() > last_frame + frame_ms) {
        last_frame = millis();
        return true;
    }
    return false;
}

bool is_new_sim_time() {
    if (millis() > last_sim + sim_ms) {
        last_sim = millis();
        return true;
    }
    return false;
}

void set_sim_ms(unsigned long ms) {
    sim_ms = ms;
}