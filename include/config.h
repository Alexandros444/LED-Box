#ifndef CONFIG_H
#define CONFIG_H

#define RECV_PIN 19
#define PIN_WS2812B 21  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 256   // The number of LEDs (pixels) on WS2812B LED strip
#define PIXELS_HEIGHT 8
#define PIXELS_WIDTH 32
#define CHAR_WIDTH 5
#define CHAR_N CHAR_WIDTH * PIXELS_HEIGHT
#define MAX_CHARS PIXELS_WIDTH / CHAR_WIDTH

#endif