#include "timing.h"

unsigned long frame_ms = 32;
// unsigned long sim_ms = 100;
unsigned long last_frame = 0;
// unsigned long last_sim = 0;

bool is_new_frame_time() {
    if (millis() > last_frame + frame_ms) {
        last_frame = millis();
        return true;
    }
    return false;
}


unsigned long tick_time[256] = { 0 };
byte tick_time_index = 0;

void tick() {
    if (tick_time_index == 255) {
        Serial.println("Tick overflow");
        return;
    }
    tick_time[tick_time_index++] = micros();
}

void tock(String msg) {
    Serial.printf("%s: %ld\n\r", msg, micros() - tick_time[--tick_time_index]);
}

void tockTick(String msg) {
    if (tick_time_index != 0)
        tock(msg);
    tick();
}

// bool is_new_sim_time() {
//     if (millis() > last_sim + sim_ms) {
//         last_sim = millis();
//         return true;
//     }
//     return false;
// }

// void set_sim_ms(unsigned long ms) {
//     sim_ms = ms;
// }