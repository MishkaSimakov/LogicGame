#include "Game.h"

Game::Game() : m_window("Logic Game X", sf::Vector2u(800, 600)), m_state_manager(&m_context) {
    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.getEventManager();

    m_state_manager.switchTo(StateType::MainMenu);
}

Game::~Game() {}

Window *Game::getWindow() {
    return &m_window;
}

void Game::update() {
    m_window.update(); // Update window events.
    m_state_manager.update(m_elapsed);
}

void Game::render() {
    m_window.beginDraw();

    m_state_manager.draw();

    m_window.endDraw();
}

void Game::lateUpdate() {
    m_state_manager.processRequests();
    restartClock();
}

sf::Time Game::getElapsed() {
    return m_elapsed;
}

void Game::restartClock() {
    m_elapsed = m_clock.restart();
}