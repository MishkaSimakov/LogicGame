#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager *stateManager) :
        BaseState(stateManager),
        m_start_game_btn(
                stateManager->getContext(),
                StateType::MainMenu,
                m_btn_size
        ),
        m_choose_level_btn(
                stateManager->getContext(),
                StateType::MainMenu,
                m_btn_size
        ),
        m_quit_game_btn(
                stateManager->getContext(),
                StateType::MainMenu,
                m_btn_size
        ),
        m_game_title(
                L"Логические цепи",
                ResourceHolder::get().fonts.get(Constants::Paths::main_font_filename)
        ) {
    sf::Vector2f window_size{stateManager->getContext()->m_wind->getWindowSize()};

    int font_size = 75;
    float start_y = (window_size.y - m_btn_size.y * 3 - m_btn_offset * 3 - (float) font_size) / 2.f;

    m_game_title.setCharacterSize(font_size);

    auto textRect = m_game_title.getLocalBounds();
    m_game_title.setOrigin(textRect.left + textRect.width / 2.0f, 0);

    m_game_title.setPosition(
            window_size.x / 2.f,
            start_y
    );
    m_game_title.setFillColor(sf::Color::Black);

    m_start_game_btn.setPosition(
            (window_size.x - m_btn_size.x) / 2.f,
            start_y + m_btn_offset + (float) font_size
    );
    m_start_game_btn.setString(
            (m_stateManager->getContext()->m_level_manager->getCurrentLevelId() == 0) ? L"Начать" : L"Продолжить"
    );
    m_start_game_btn.setOnClickCallback(&MainMenuState::startGame, this);


    m_choose_level_btn.setPosition(
            (window_size.x - m_btn_size.x) / 2.f,
            start_y + m_btn_offset * 2 + m_btn_size.y + (float) font_size
    );
    m_choose_level_btn.setString(L"Выбрать уровень");
    m_choose_level_btn.setOnClickCallback(&MainMenuState::chooseLevel, this);


    m_quit_game_btn.setPosition(
            (window_size.x - m_btn_size.x) / 2.f,
            start_y + m_btn_offset * 3 + m_btn_size.y * 2 + (float) font_size
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
    m_choose_level_btn.setVisible(true);
    m_quit_game_btn.setVisible(true);
}

void MainMenuState::deactivate() {
    m_start_game_btn.setVisible(false);
    m_choose_level_btn.setVisible(false);
    m_quit_game_btn.setVisible(false);
}

void MainMenuState::update(const sf::Time &time) {

}

void MainMenuState::draw() {
    m_stateManager->getContext()->m_wind->draw(m_game_title);

    m_stateManager->getContext()->m_wind->draw(m_start_game_btn);
    m_stateManager->getContext()->m_wind->draw(m_choose_level_btn);
    m_stateManager->getContext()->m_wind->draw(m_quit_game_btn);
}

void MainMenuState::startGame() {
    m_stateManager->switchTo(StateType::Level);
}

void MainMenuState::quitGame() {
    m_stateManager->getContext()->m_wind->close();
}

void MainMenuState::chooseLevel() {
    m_stateManager->switchTo(StateType::LevelChoose);
}
