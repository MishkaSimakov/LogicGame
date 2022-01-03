#include "LevelState.h"
#include "StateManager.h"

LevelState::LevelState(StateManager *stateManager) :
        BaseState(stateManager),
        m_simulation_manager(
                stateManager->getContext(),
                ResourceHolder::get().levels.get("1").getInputsCount(),
                ResourceHolder::get().levels.get("1").getOutputsCount()
        ),
        m_components_block(
                {m_documentation_block_width + 25, 1080 - 120 - 25},
                {
                        (float) stateManager->getContext()->m_wind->getRenderWindow()->getSize().x -
                        m_documentation_block_width - 25 * 2, 120
                },
                stateManager->getContext()
        ),
        m_documentation_block(
                ResourceHolder::get().levels.get("1").getTitle(),
                ResourceHolder::get().levels.get("1").getDescription(),
                {m_documentation_block_width,
                 (float) stateManager->getContext()->m_wind->getRenderWindow()->getSize().y},
                stateManager->getContext()
        ),
        m_level_result_window(
                stateManager->getContext(),
                m_result_window_size,
                ((sf::Vector2f) stateManager->getContext()->m_wind->getRenderWindow()->getSize() -
                 m_result_window_size) / 2.f
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

    stateManager->getContext()->m_eventManager->addKeyPressedCallback(
            StateType::Level, sf::Keyboard::Space,
            &LevelState::startSimulation, this
    );

    m_components_block.addStaticComponent(&m_and_data);
    m_components_block.addStaticComponent(&m_or_data);
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
    m_documentation_block.update(time);
}

void LevelState::draw() {
    m_simulation_manager.draw();
    m_components_block.draw();
    m_documentation_block.draw();
    m_level_result_window.draw();
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

void LevelState::startSimulation(const sf::Event &event) {
    int wrong_count = 0;

    for (bool *test: ResourceHolder::get().levels.get("1").getTests()) {
        if (!m_simulation_manager.runSimulationTest(test)) {
            ++wrong_count;
        }
    }

    m_level_result_window.showWithResult(LevelResultWindow::LevelResult::SUCCESS);
}
