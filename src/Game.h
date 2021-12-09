#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "MainMenuState.h"
#include "Event.h"
#include <memory>
#include <vector>

class Game
{
public:
    Game();
    void run();

    template <typename T, typename... Args>
    void pushState(Args&&... args);

    void pushState(std::unique_ptr<BaseState> state);

    void popState();
    void exitGame();

    template <typename T, typename... Args>
    void changeState(Args&&... args);

    const sf::RenderWindow& getWindow() const;
private:
    void handleEvent();
    void tryPopState();

    BaseState &getCurrentState();

    std::vector<std::unique_ptr<BaseState>> m_states;

    sf::RenderWindow m_window;

    bool m_shouldPopState = false;
    bool m_shouldExit = false;
    bool m_shouldChangeState = false;
    std::unique_ptr<BaseState> m_change;
};

template <typename T, typename... Args>
inline void Game::pushState(Args&&... args)
{
    pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
void Game::changeState(Args&&... args)
{
    m_change = std::make_unique<T>(std::forward<Args>(args)...);
    m_shouldPopState = true;
    m_shouldChangeState = true;
}

#endif // GAME_H
