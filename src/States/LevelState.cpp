#include "LevelState.h"
#include "StateManager.h"

LevelState::LevelState(StateManager *stateManager) :
        BaseState(stateManager),
        m_layout((sf::Vector2f) stateManager->getContext()->m_wind->getWindowSize()),
        m_simulation_manager(stateManager->getContext()),
        m_components_block(
                {m_documentation_block_width + 25, 1080 - 120 - 25},
                {
                        (float) stateManager->getContext()->m_wind->getRenderWindow()->getSize().x -
                        m_documentation_block_width - 25 * 2, 120
                },
                stateManager->getContext()
        ),
        m_documentation_block(
                *m_stateManager->getContext()->m_level_manager->getCurrentLevel(),
                m_layout,
                stateManager->getContext()
        ),
        m_level_controls(
                stateManager->getContext(),
                &LevelState::runTests,
                &LevelState::mainMenu,
                this
        ) {
    m_loaded_level_id = m_stateManager->getContext()->m_level_manager->getCurrentLevelId();

    stateManager->getContext()->m_eventManager->addMouseReleasedCallback(
            StateType::Level, sf::Mouse::Left,
            &SimulationManager::handleMouseReleased, &m_simulation_manager
    );
    stateManager->getContext()->m_eventManager->addEventCallback(
            StateType::Level, sf::Event::MouseMoved,
            &SimulationManager::handleMouseMove, &m_simulation_manager
    );
    stateManager->getContext()->m_eventManager->addKeyReleasedCallback(
            StateType::Level, sf::Keyboard::BackSpace,
            &SimulationManager::deleteSelectedShape, &m_simulation_manager
    );

    stateManager->getContext()->m_eventManager->addMousePressedCallback(
            StateType::Level, sf::Mouse::Left,
            &LevelState::handleMousePressed, this
    );

    for (auto &allowed_component: m_stateManager->getContext()->m_level_manager->getCurrentLevel()->getAllowedComponents()) {
        m_components_block.addStaticComponent(
                m_components_data.getComponentData(allowed_component)
        );
    }
}

void LevelState::onCreate() {
}

void LevelState::onDestroy() {
}

void LevelState::activate() {
    if (m_stateManager->getContext()->m_level_manager->getCurrentLevelId() != m_loaded_level_id) {
        reloadLevel();
    }
}

void LevelState::deactivate() {
}

void LevelState::update(const sf::Time &time) {
    m_simulation_manager.update(time);
    m_documentation_block.update(time);

    if (m_documentation_block.getState() == DocumentationBlock::State::CLOSING ||
        m_documentation_block.getState() == DocumentationBlock::State::OPENING) {

        float window_width = (float) m_stateManager->getContext()->m_wind->getWindowSize().x;
        float available_width = window_width - m_documentation_block.getPosition();

        float max_offset = 250.f;
        float min_offset = 25.f;
        float x_offset = (available_width - (window_width - m_documentation_block_width))
                         / m_documentation_block_width * (max_offset - min_offset) + min_offset;

        m_components_block.setSize(
                {
                        available_width - x_offset * 2,
                        120.f
                }
        );
        m_components_block.setPosition(
                {
                        m_documentation_block.getPosition() + x_offset,
                        (float) m_stateManager->getContext()->m_wind->getWindowSize().y - 25 -
                        m_components_block.getSize().y
                }
        );
    }
}

void LevelState::draw() {
    m_simulation_manager.draw();
    m_components_block.draw();
    m_documentation_block.draw();
    m_level_controls.draw();
}

void LevelState::handleMousePressed(const sf::Event &event) {
    sf::Vector2f mouse_pos{m_stateManager->getContext()->m_wind->getMousePosition()};

    if (auto data = m_components_block.getClickedComponentData(mouse_pos)) {
        m_simulation_manager.addLogicalComponent(data.value().first, data.value().second);
        return;
    }

    m_simulation_manager.handleMousePressed(event);
}

void LevelState::runTests() {
    int wrong_count = 0;

    for (auto &[test_inputs, test_outputs]: m_stateManager->getContext()->m_level_manager->getCurrentLevel()->getTests()) {
        if (!m_simulation_manager.runSimulationTest(test_inputs, test_outputs)) {
            ++wrong_count;
        }
    }

    m_stateManager->getContext()->m_level_manager->setPassedTestsCount(
            (int) m_stateManager->getContext()->m_level_manager->getCurrentLevel()->getTests().size() - wrong_count
    );

    m_simulation_manager.resetInputs();

    m_stateManager->switchTo(StateType::LevelResult);
}

void LevelState::mainMenu() {
    m_stateManager->switchTo(StateType::MainMenu);
}

void LevelState::reloadLevel() {
    auto level = m_stateManager->getContext()->m_level_manager->getCurrentLevel();

    m_documentation_block.setLevel(*level);

    m_simulation_manager = SimulationManager(
            m_stateManager->getContext()
    );

    m_components_block.clearStaticComponents();
    for (auto &allowed_component: level->getAllowedComponents()) {
        m_components_block.addStaticComponent(
                m_components_data.getComponentData(allowed_component)
        );
    }

    m_loaded_level_id = m_stateManager->getContext()->m_level_manager->getCurrentLevelId();
}
