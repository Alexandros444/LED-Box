#ifndef uint8_t
#include <Arduino.h>
#endif

/**
 *  Mapping:
 * 0 8 ... 248
 * 1       ...
 * ...
 * 7   ... 255
 *
 */


uint8_t pos_to_idx(int x, int y) {
    if (x < 0 || x > 31 || y < 0 || y > 7)
        return 0;
    return x * 8 + y;
}



const uint8_t K[] = {
    1,  0,  0,  1,
    1,  0,  0,  1,
    1,  0,  1,  0,
    1,  1,  0,  0,
    1,  1,  0,  0,
    1,  0,  1,  0,
    1,  0,  0,  1,
    1,  0,  0,  1,
};
