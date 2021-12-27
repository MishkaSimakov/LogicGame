#ifndef GAME_H
#define GAME_H

#include "SharedContext.h"
#include "StateManager.h"
#include "Window.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class Game {
public:
    Game();
    ~Game();

    void update();
    void render();
    void lateUpdate();

    Window *getWindow();

    sf::Time getElapsed();
    void restartClock();
private:
    Window m_window;
    StateManager m_state_manager;
    SharedContext m_context;

    sf::Clock m_clock;
    sf::Time m_elapsed;
};

#endif // GAME_H
