//
// Created by lucian on 03.12.2017.
//

#ifndef BALLFALL_V2_BALLFALL_H
#define BALLFALL_V2_BALLFALL_H

#define DISPLAY_WIDTH 8
#define DISPLAY_HEIGHT 8
#define PADS_NUM 3

#define BALL_INIT_POS_X 3
#define BALL_INIT_POS_Y 0

#define OFFSET_SCREEN_X 0
#define OFFSET_SCREEN_Y 0

#define PAD_WIDTH 5
#define PAD_SPACING 2

int get_random(int min, int max);

typedef unsigned long int height_type;

class ball_fall {

    int lifes = 1;
    height_type score = 0;

    struct pad {
        char x;
        height_type y;
        char length;

        pad() : x(0), y(0), length(0) {}

        pad(char x, height_type y, char length) : x(x), y(y), length(length) {}

        char left() {
            return x;
        }

        char right() {
            return (char) (x + length - 1);
        }
    };

    struct ball {
        char x;
        height_type y;
        pad* current_pad;
        ball(char x, height_type y) : x(x), y(y), current_pad(nullptr) {}
    } player_ball;

    struct view_point {
        char x;
        height_type y;
        char width;
        char height;
        view_point(char x, height_type y) : x(x), y(y), width(DISPLAY_WIDTH), height(DISPLAY_HEIGHT) {}

        void print_matrix(char (*screen)[8], const ball &ball, const pad* pads) const;

        void print(char screen[DISPLAY_HEIGHT], const ball &ball, pad pads[]);
    } current_view_point;

    pad pads[PADS_NUM];

    height_type last_pad_height;

    void attach_ball();

    pad generate_pad(height_type &lph);

    void init_pads();

public:
    ball_fall();

    void move_ball(char direction);

    height_type drop_ball();

    bool pads_up();

    void start_game();

    void reset();

    void print_matrix(char (*screen)[8]) const;

    void add_life();

    int get_lifes();

    void print(char screen[DISPLAY_HEIGHT]);

    height_type get_score() { return score; }
};


#endif //BALLFALL_V2_BALLFALL_H
