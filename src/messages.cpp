#include "messages.h"

uint32_t *background[] = {(uint32_t *) frame_red_yellow2, (uint32_t*)frame_red_yellow};
size_t frame_size[] = {frame_red_yellow2_size,frame_red_yellow_size};
int frame_idx = 0;
bool background_active = false;

char *string_roll[] = {
    (char*)kalina_greeting,
    (char*)quoutes,
    (char*)kalina_laengsten,
    (char*)kalina_subwoofer,
    (char*)heilendes_sperma,
    (char*)wasser_hoeschen,
    (char*)im_arsch,
    (char*)kopfschmerzen,
    (char*)popel,
    (char*)klappe,
    (char*)dick,
    (char*)brain_cell,
    (char*)schwanger,
    (char*)big_dick,
    (char*)sugar_mommy,
    (char*)gut_gehalten,
    (char*)etsu,
};

void toggle_background() {
    background_active = !background_active;
}

int str_idx = 0;
int str_max_idx = sizeof(string_roll) / sizeof(char*);

void disp_message(){
    static unsigned long background_change_time = 0;
    if (background_active){
        led_disp_frame(background[frame_idx],frame_size[frame_idx]);
        frame_idx = (frame_idx+1) % (sizeof(frame_size) / sizeof(size_t));
    }

    if (scroll_disp_str(string_roll[str_idx],!background_active,3))
        str_idx = (str_idx +1) % str_max_idx;
}


void run_message(){

}


