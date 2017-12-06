//
// Created by lucian on 03.12.2017.
//

#include "ball_fall.h"


void ball_fall::view_point::print_matrix(char (*screen)[8], const ball_fall::ball &ball, const ball_fall::pad* pads) const {
    for (char i = 0; i < DISPLAY_HEIGHT; i++) {
        for (char j = 0; j < DISPLAY_WIDTH; j++) {
            screen[i][j] = 0;
        }
    }

    for (char i = 0; i < PADS_NUM; i++) {
        height_type pad_y = pads[i].y - this->y;
        if (pad_y < 0 || pad_y >= DISPLAY_HEIGHT) continue;
        for (char j = 0; j < pads[i].length && j < DISPLAY_WIDTH; j++) {
            screen[pad_y][j + pads[i].x] = 1;
        }
    }
    screen[ball.y - this->y][ball.x - this->x] = 1;
}

void ball_fall::view_point::print(char *screen, const ball_fall::ball &ball, ball_fall::pad pads[]) {
    char helper_screen[DISPLAY_HEIGHT][DISPLAY_WIDTH];
    print_matrix(helper_screen, ball, pads);

    for(char i = 0; i < DISPLAY_HEIGHT; i++) {
        screen[i] = 0;
        for (char j = 0; j < DISPLAY_WIDTH; j++) {
            if (helper_screen[i][j] == 1) {
                screen[i] = (char)(screen[i] | (1 << j));
            }
        }
    }
}

void ball_fall::attach_ball() {
    player_ball.current_pad = nullptr;
    for (auto &current_pad : pads) {
        if (current_pad.y == player_ball.y + 1 && current_pad.left() <= player_ball.x && player_ball.x <= current_pad.right()) {
            player_ball.current_pad = &current_pad;
            return;
        }
    }
}

ball_fall::pad ball_fall::generate_pad(height_type &lph) {
    lph = lph + PAD_SPACING + 1;

    return {(char) get_random(0, DISPLAY_WIDTH - PAD_WIDTH), lph, PAD_WIDTH};
}

void ball_fall::init_pads() {
    height_type pad_1_h = BALL_INIT_POS_Y + 1;
    pads[0] = pad(0, pad_1_h, DISPLAY_WIDTH);
    last_pad_height = pad_1_h;

    for (int i = 1; i < PADS_NUM; i++) {
        pads[i] = generate_pad(last_pad_height);
    }
}

void ball_fall::move_ball(char direction) {
    direction = (char) (direction < 0 ? -1 : direction == 0 ? 0 : 1);
    char new_x = player_ball.x + direction;
    if (new_x >= 0 && new_x < DISPLAY_WIDTH) player_ball.x = new_x;
    attach_ball();
}

height_type ball_fall::drop_ball() {
    this -> score += 1;
    if (player_ball.current_pad == nullptr) {
        player_ball.y += 1;
        attach_ball();
        if (player_ball.y - current_view_point.y == DISPLAY_HEIGHT - 1) current_view_point.y += 1;
    }
    return score;
}

bool ball_fall::pads_up() {
    if (player_ball.current_pad != nullptr && player_ball.current_pad->y <= current_view_point.y + 1) {
        lifes--;
        if (lifes <= 0) return false;
        player_ball.y += 4;
        attach_ball();
        return true;
    }

    for (char i = 0; i < PADS_NUM; i++) {
        if (pads[i].y <= current_view_point.y) {
            pads[i] = generate_pad(last_pad_height);
            continue;
        }
        pads[i].y -= 1;
    }

    if (player_ball.current_pad != nullptr) {
        player_ball.y = player_ball.current_pad->y - 1;
    }

    last_pad_height--;
    return true;
}

void ball_fall::start_game() {
    pads[0] = generate_pad(last_pad_height);
    attach_ball();
}

void ball_fall::print_matrix(char (*screen)[8]) const {
    current_view_point.print_matrix(screen, player_ball, pads);
}

void ball_fall::print(char *screen) {
    current_view_point.print(screen, player_ball, pads);
}

ball_fall::ball_fall() : last_pad_height(0),
                         player_ball(BALL_INIT_POS_X, BALL_INIT_POS_Y),
                         current_view_point(OFFSET_SCREEN_X, -OFFSET_SCREEN_Y) {
    reset();
}

void ball_fall::reset() {
    current_view_point.x = OFFSET_SCREEN_X;
    current_view_point.y = -OFFSET_SCREEN_Y;

    player_ball.x = BALL_INIT_POS_X;
    player_ball.y = BALL_INIT_POS_Y;

    score = 0;
    lifes = 1;

    init_pads();
    attach_ball();
}

void ball_fall::add_life() {
    this->lifes += 1;
}

int ball_fall::get_lifes() {
    return this->lifes;
}
