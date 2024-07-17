#include "led.h"

Adafruit_NeoPixel ws2812b_2(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

bool is_on = true;
uint8_t brightness = 10;
uint8_t max_bright = 150;
uint8_t step_bright = 15;

void led_begin() {
    ws2812b_2.begin();
}

void led_clear() {
    ws2812b_2.clear();
}

void led_show() {
    if (!is_on)
        ws2812b_2.clear();
    ws2812b_2.show();
}
void turn_disp_off() {
    is_on = false;
}
void turn_disp_on() {
    is_on = true;
}

byte get_brightness() {
    return brightness;
}

void led_set_true_color(byte n, byte r, byte g, byte b) {
    r = r * brightness / 255;
    g = g * brightness / 255;
    b = b * brightness / 255;
    ws2812b_2.setPixelColor(n, ws2812b_2.Color(r, g, b));
}

void led_set_data(byte n, byte r, byte g, byte b) {
    ws2812b_2.setPixelColor(n, ws2812b_2.Color(brightness * (r & 0x1), brightness * (g & 0x1), brightness * (b & 0x1)));
}


void change_brightness_step() {
    if (brightness < 100) step_bright = 25;
    if (brightness < 40) step_bright = 5;
    if (brightness < 10) step_bright = 1;
}

void inc_brightness() {
    change_brightness_step();
    brightness += step_bright;
    if (brightness > max_bright)brightness = max_bright;
    Serial.print(brightness);
}

void dec_brightness() {
    change_brightness_step();
    uint8_t newBrightness = brightness - step_bright;
    if (brightness < newBrightness) brightness = 0;
    else brightness = newBrightness;
    Serial.print(brightness);
}

