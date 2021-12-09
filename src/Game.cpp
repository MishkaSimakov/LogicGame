#include "Game.h"

Game::Game() : m_window({1280, 720}, L"Логическая игра") {
    m_window.setPosition({m_window.getPosition().x, 0});
    m_window.setFramerateLimit(60);
    pushState<MainMenuState>(*this);
}

void Game::run() {
    sf::Clock timer;

    auto lastTime = sf::Time::Zero;

    while (m_window.isOpen() && !m_states.empty()) {
        BaseState &state = getCurrentState();

        // calculate time
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;

        // real time update
        state.handleInput();
        state.update(elapsed);

        // render
        m_window.clear();
        state.render(m_window);
        m_window.display();

        // handle events
        handleEvent();
        tryPopState();
    }
}

void Game::tryPopState() {
    if (m_shouldPopState) {
        m_shouldPopState = false;

        if (m_shouldExit) {
            m_states.clear();
            return;
        } else if (m_shouldChangeState) {
            m_shouldChangeState = false;
            m_states.pop_back();
            pushState(std::move(m_change));
            return;
        }

        m_states.pop_back();
    }
}

void Game::popState() {
    m_shouldPopState = true;
}

void Game::exitGame() {
    m_shouldPopState = true;
    m_shouldExit = true;
}

void Game::handleEvent() {
    // custom event class that stores window data (that cannot be changed)
    Event e;

    while (m_window.pollEvent(e)) {
        e.setRenderTarget(m_window);
        getCurrentState().handleEvent(e);

        if (e.type == sf::Event::Closed) {
            m_window.close();
        } else if (e.type == sf::Event::Resized) {
            m_window.setView(sf::View({
                                              0,
                                              0,
                                              static_cast<float>(e.size.width),
                                              static_cast<float>(e.size.height)
                                      }));
        }
    }
}

BaseState &Game::getCurrentState() {
    return *m_states[0];
}

void Game::pushState(std::unique_ptr<BaseState> state) {
    m_states.push_back(std::move(state));
}

const sf::RenderWindow &Game::getWindow() const {
    return m_window;
}
