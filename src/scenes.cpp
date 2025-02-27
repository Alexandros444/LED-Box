#include "scenes.h"

int current_scene = KALINA;
const int num_scenes = 3;

char *disp_str[] = {(char*)kalina_greeting,(char*)kalina_laengsten, (char*)kalina_subwoofer};
int disp_str_idx = 0;
int disp_str_size = sizeof(disp_str) / sizeof(char*);

void switch_scene() {
    current_scene = (current_scene + 1) % num_scenes;
    Serial.printf("Active Scene %d\n",current_scene);
    start_new_scene();
}

void set_scene(int scene) {
    if (current_scene == scene)
        return;
    current_scene = scene;
    Serial.printf("Active Scene %d\n",current_scene);
    start_new_scene();
}


void start_new_scene() {
    switch (current_scene)
    {
    case KALINA:
        break;
    case SNAKE:
        clear_cells();
        step_snake_game();
        break;
    case CELL:
        clear_cells();
        random_splash(30);
        random_splash(30);
        random_splash(30);
        random_splash(30);
        break;
    case ANIM:
        break;
    case WEB:
        web_start();
        break;
    default:
        break;
    }
}

void run_scene() {
    switch (current_scene)
    {
    case KALINA:
        break;
    case SNAKE:
        step_snake_game();
        break;
    case CELL:
        run_cells_step();
        break;
    case ANIM:
        break;
    case WEB:
        web_run();
        break;
    default:
        break;
    }
}

void end_scene() {
    switch (current_scene)
    {
    case KALINA:
        set_color(WHITE);
        break;
    case SNAKE:
        break;
    case CELL:
        break;
    case ANIM:
        break;
    case WEB:
        web_stop();
        break;
    default:
        break;
    }
}

void disp_scene() {
    switch (current_scene)
    {
    case KALINA:
        // tick();
        disp_message();
        // if (scroll_disp_str(disp_str[disp_str_idx], true, 2))
        //     disp_str_idx=(disp_str_idx+1) % disp_str_size;
        // tock("Scroll Disp");
        break;
    case SNAKE:
        disp_snake_game();
        break;
    case CELL:
        disp_cells(100, 100, 0);
        break;
    case ANIM:
        break;
    case WEB:
        disp_web();
        break;
    default:
        break;
    }
}

int activate_web = 3;
unsigned long activate_web_last_input_time = 0;
int activate_auto_snake = 3;
unsigned long activate_auto_snake_last_input_time = 0;

void scene_handle_input(uint32_t code) {
    switch (code) {
    case Off_code:
        turn_disp_off();
        break;
    case On_code:
        if (millis() > activate_web_last_input_time + 10000)
            activate_web = 3;
        activate_web--;
        activate_web_last_input_time = millis();
        turn_disp_on();
        if (activate_web <= 0) {
            set_scene(WEB);
            activate_web = 3;
        }
        break;
    case bright_code:
        inc_brightness();
        break;
    case dim_code:
        dec_brightness();
        break;
    case R_code:
        inc_game_speed();
        inc_scroll_speed();
        inc_cell_speed();
        // set_color(RED);
        break;
    case SPEEDTWO:
        inc_game_speed();
        inc_scroll_speed();
        inc_cell_speed();
        // set_color(RED);
        break;
    case B_code:
        dec_game_speed();
        dec_scroll_speed();
        dec_cell_speed();
        // set_color(BLUE);
        break;
    case SLOWTWO:
        dec_game_speed();
        dec_scroll_speed();
        dec_cell_speed();
        // set_color(BLUE);
        break;
    case G_code:
        toggle_bounce();
        // set_color(GREEN);
        break;
    case Orange_code:
        set_color(RED);
        break;
    case Blue_code:
        set_color(BLUE);
        break;    
    case W_code:
        set_color(WHITE);
        break;
    case Green_code:
        steer_snake(UP);
        set_color(GREEN);
        break;
    case Purple_code:
        steer_snake(RIGHT);
        set_color(PURPLE);
        break;
    case Teal2_code:
        steer_snake(DOWN);
        break;
    case Orange2_code:
        steer_snake(LEFT);
        break;
    case Strobe_code:
        random_splash(50);
        break;
    case Fade_code:
        clear_cells();
        break;
    case Flash_code:
        toggle_background();
        break;
    case FLASHTWO:
        toggle_background();
        break;
    case Smooth_code:
        switch_scene();
        break;
    case FADETWO:
        switch_scene();
        break;
    case Pink_code:
        set_color(PINK);
        break;
    case Teal_code:
        set_color(TEAL);
        if (millis() > activate_auto_snake_last_input_time + 5000)
            activate_auto_snake = 3;
        activate_auto_snake--;
        activate_auto_snake_last_input_time = millis();
        turn_disp_on();
        if (activate_auto_snake <= 0) {
            start_auto_move();
            activate_auto_snake = 3;
        }
        break;
    case DMX:
        set_color(TEAL);
        if (millis() > activate_auto_snake_last_input_time + 5000)
            activate_auto_snake = 3;
        activate_auto_snake--;
        activate_auto_snake_last_input_time = millis();
        turn_disp_on();
        if (activate_auto_snake <= 0) {
            start_auto_move();
            activate_auto_snake = 3;
        }
        break;
    default:
        // Serial.print("Cant find Code: ");
        // Serial.println(code, HEX);
        break;
    }
}