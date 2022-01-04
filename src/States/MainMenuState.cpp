#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager *stateManager) :
        BaseState(stateManager),
        m_start_game_btn(
                stateManager->getContext(),
                StateType::MainMenu,
                m_btn_size
        ),
        m_quit_game_btn(
                stateManager->getContext(),
                StateType::MainMenu,
                m_btn_size
        ) {
    sf::Vector2f window_size{stateManager->getContext()->m_wind->getWindowSize()};

    m_start_game_btn.setPosition(
            {
                    (window_size.x - m_btn_size.x) / 2.f,
                    (window_size.y - m_btn_size.y * 2 - m_btn_offset) / 2.f
            }
    );
    m_start_game_btn.setString(L"Начать");
    m_start_game_btn.setOnClickCallback(&MainMenuState::startGame, this);

    m_quit_game_btn.setPosition(
            {
                    (window_size.x - m_btn_size.x) / 2.f,
                    (window_size.y - m_btn_size.y * 2 - m_btn_offset) / 2.f + m_btn_size.y + m_btn_offset
            }
    );
    m_quit_game_btn.setString(L"Выйти");
    m_quit_game_btn.setOnClickCallback(&MainMenuState::quitGame, this);
}

void MainMenuState::onCreate() {
}

void MainMenuState::onDestroy() {

}

void MainMenuState::activate() {
    m_start_game_btn.setVisible(true);
    m_quit_game_btn.setVisible(true);
}

void MainMenuState::deactivate() {
    m_start_game_btn.setVisible(false);
    m_quit_game_btn.setVisible(false);
}

void MainMenuState::update(const sf::Time &time) {

}

void MainMenuState::draw() {
    m_stateManager->getContext()->m_wind->draw(m_start_game_btn);
    m_stateManager->getContext()->m_wind->draw(m_quit_game_btn);
}

void MainMenuState::startGame() {
    m_stateManager->switchTo(StateType::Level);
}

void MainMenuState::quitGame() {
    m_stateManager->getContext()->m_wind->close();
}
