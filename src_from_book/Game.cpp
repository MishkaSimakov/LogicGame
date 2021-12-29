#include "Game.h"

Game::Game() : m_window("Logic Game X", sf::Vector2u(800, 600)), m_stateManager(&m_context) {
    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.GetEventManager();

    m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() {}

Window *Game::GetWindow() {
    return &m_window;
}

void Game::Update() {
    m_window.Update(); // Update window events.
    m_stateManager.Update(m_elapsed);
}

void Game::Render() {
    m_window.BeginDraw();

    m_stateManager.Draw();

    m_window.EndDraw();
}

void Game::LateUpdate() {
    m_stateManager.ProcessRequests();
    RestartClock();
}

sf::Time Game::GetElapsed() {
    return m_elapsed;
}

void Game::RestartClock() {
    m_elapsed = m_clock.restart();
}