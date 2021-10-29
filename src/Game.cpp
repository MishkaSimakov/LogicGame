#include "Game.h"
#include <iostream>

Game::Game() : m_window({1280, 720}, "Logic game")
{
    m_window.setPosition({m_window.getPosition().x, 0});
    m_window.setFramerateLimit(60);
    pushState<TestState>(*this);
}

void Game::run()
{
    sf::Clock timer;

    auto lastTime = sf::Time::Zero;

    while (m_window.isOpen())
    {
        BaseState &state = getCurrentState();

        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;

        state.handleInput();
        state.update(elapsed);

        m_window.clear();
        state.render(m_window);
        m_window.display();

        handleEvent();
    }
}

void Game::handleEvent()
{
    sf::Event e;

    while (m_window.pollEvent(e))
    {
        getCurrentState().handleEvent(e);

        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

BaseState &Game::getCurrentState()
{
    return *m_states.back();
}

void Game::pushState(std::unique_ptr<BaseState> state)
{
    m_states.push_back(std::move(state));
}
