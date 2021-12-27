#include "MainMenuState.h"
#include "StateManager.h"

void MainMenuState::onCreate() {
    m_rectangle.setPosition({10, 10});
    m_rectangle.setFillColor(sf::Color::Red);
    m_rectangle.setSize({100, 100});
}

void MainMenuState::onDestroy() {

}

void MainMenuState::activate() {

}

void MainMenuState::deactivate() {

}

void MainMenuState::update(const sf::Time &time) {

}

void MainMenuState::draw() {
    m_stateManager->getContext()->m_wind->draw(m_rectangle);
}
