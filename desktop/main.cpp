#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../ball_fall.h"

using namespace std;

int get_random(int min, int max) {
    int r = rand() % (max - min + 1) + min;
    return r;
}

void print(const ball_fall &game) {
    char screen[DISPLAY_HEIGHT][DISPLAY_WIDTH];
    game.print_matrix(screen);
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            cout<<(int)screen[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

int main() {
    srand(time(NULL));

    ball_fall game;

    game.reset();

    game.start_game();

    while(true) {
        game.pads_up();
        game.drop_ball();
        game.move_ball(get_random(0, 1) == 0 ? -1 : 1);
        print(game);
    }

    return 0;
}
