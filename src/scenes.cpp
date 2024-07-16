#include "scenes.h"


void switch_scene() {
    current_scene = (current_scene + 1) % num_scenes;
    Serial.printf("Active Scene %d\n",current_scene);
    start_new_scene();
}

void set_scene(int scene) {
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
        step_snake_game();
        break;
    case CELL:
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
        break;
    case SNAKE:
        break;
    case CELL:
        clear_cells();
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
        scroll_disp_str("KALINA!", true);
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
        web_disp();
        break;
    default:
        break;
    }
}

int activate_web_server = 3;

void scene_handle_input(uint32_t code) {
    switch (code) {
    case Off_code:
        turn_disp_off();
        break;
    case On_code:
        activate_web_server--;
        turn_disp_on();
        if (activate_web_server <= 0) {
            set_scene(WEB);
            activate_web_server = 3;
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
    case Flash_code:
        break;
    case Smooth_code:
        switch_scene();
        break;

    default:
        // Serial.print("Cant find Code: ");
        // Serial.println(code, HEX);
        break;
    }
}