#include "LevelState.h"
#include "StateManager.h"

LevelState::LevelState(StateManager *stateManager) :
        BaseState(stateManager),
        m_simulation_manager(stateManager->getContext()),
        m_components_block(
                {500, 1080 - 120 - 25},
                {750, 120},
                stateManager->getContext()
        ) {
    stateManager->getContext()->m_eventManager->addMouseReleasedCallback(
            StateType::Level, sf::Mouse::Left,
            &SimulationManager::handleMouseReleased, &m_simulation_manager
    );
    stateManager->getContext()->m_eventManager->addEventCallback(
            StateType::Level, sf::Event::MouseMoved,
            &SimulationManager::handleMouseMove, &m_simulation_manager
    );

    stateManager->getContext()->m_eventManager->addMousePressedCallback(
            StateType::Level, sf::Mouse::Left,
            &LevelState::handleMousePressed, this
    );

    m_components_block.addStaticComponent(And());
}

void LevelState::onCreate() {

}

void LevelState::onDestroy() {

}

void LevelState::activate() {

}

void LevelState::deactivate() {

}

void LevelState::update(const sf::Time &time) {
    m_simulation_manager.update();
}

void LevelState::draw() {
    m_simulation_manager.draw();
    m_components_block.draw();
}

void LevelState::handleMousePressed(const sf::Event &event) {
    sf::Vector2f mouse_pos{sf::Mouse::getPosition(
            *m_stateManager->getContext()->m_wind->getRenderWindow()
    )};

    if (auto data = m_components_block.getClickedComponentData(mouse_pos)) {
        m_simulation_manager.addLogicalComponent(
                data.value().second,
                data.value().first
        );
        return;
    }

    m_simulation_manager.handleMousePressed(event);
}
