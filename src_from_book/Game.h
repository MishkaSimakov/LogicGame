#ifndef LOGICGAMEENGINE_GAME_H
#define LOGICGAMEENGINE_GAME_H

#include "Window.h"
#include "StateManager.h"

class Game {
public:
    Game();
    ~Game();

    void Update();
    void Render();
    void LateUpdate();

    Window *GetWindow();

    sf::Time GetElapsed();
    void RestartClock();
private:
    Window m_window;
    SharedContext m_context;
    StateManager m_stateManager;

    sf::Clock m_clock;
    sf::Time m_elapsed;
};


#endif //LOGICGAMEENGINE_GAME_H
