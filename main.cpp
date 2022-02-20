#include "Game.h"

int main() {
    srand(time(nullptr));

    Game game;

    while (!game.getWindow()->isDone()) {
        game.update();
        game.render();
        game.lateUpdate();
    }

    return 0;
}