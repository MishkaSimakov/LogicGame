#include "LevelChooseState.h"
#include "StateManager.h"

LevelChooseState::LevelChooseState(StateManager *stateManager) :
        BaseState(stateManager),
        m_quit_level_choose_btn(
                stateManager->getContext(),
                StateType::LevelChoose,
                m_quit_level_choose_btn_size,
                sf::Vector2f(25.f, 25.f)
        ) {
    m_level_count = (int) m_stateManager->getContext()->m_level_manager->getLevels().size();

    m_quit_level_choose_btn.setTexture(&ResourceHolder::get().textures.get(Constants::Paths::home_icon_filename));
    m_quit_level_choose_btn.setOnClickCallback(&LevelChooseState::quitLevelChoose, this);

    int row = -1;

    sf::Vector2f start_pos{
            ((float) stateManager->getContext()->m_wind->getWindowSize().x -
             (float) m_max_levels_count_x * (m_level_btn_size.y + m_offset.x)) / 2,
            ((float) stateManager->getContext()->m_wind->getWindowSize().y -
             std::ceil((float) m_level_count / (float) m_max_levels_count_x) * (m_level_btn_size.y + m_offset.y)) / 2
    };

    for (int i = 0; i < m_level_count; ++i) {
        if (i % m_max_levels_count_x == 0) ++row;

        m_level_btns.push_back(
                std::make_unique<Button>(
                        stateManager->getContext(),
                        StateType::LevelChoose,
                        m_level_btn_size
                )
        );

        if (stateManager->getContext()->m_level_manager->isLevelUnlocked(i)) {
            m_level_btns.back()->setOnClickCallback([this, i]() {
                choose(i);
            });
            m_level_btns.back()->setString(std::to_wstring(i + 1));
        } else {
            m_level_btns.back()->setEnabled(false);
            m_level_btns.back()->setTexture(&ResourceHolder::get().textures.get(Constants::Paths::locked_icon_filename));
            m_level_btns.back()->setTextureOffset(15);
        }

        m_level_btns.back()->setPosition(
                start_pos + sf::Vector2f(
                        (float) (i - row * m_max_levels_count_x) * (m_level_btn_size.x + m_offset.x),
                        (float) row * (m_level_btn_size.y + m_offset.y)
                )
        );
    }
}

void LevelChooseState::onCreate() {

}

void LevelChooseState::onDestroy() {

}

void LevelChooseState::activate() {
    m_quit_level_choose_btn.setVisible(true);

    for (auto &btn: m_level_btns) {
        btn->setVisible(true);
    }
}

void LevelChooseState::deactivate() {
    m_quit_level_choose_btn.setVisible(false);

    for (auto &btn: m_level_btns) {
        btn->setVisible(false);
    }
}

void LevelChooseState::update(const sf::Time &time) {

}

void LevelChooseState::draw() {
    for (auto &btn: m_level_btns) {
        m_stateManager->getContext()->m_wind->draw(*btn);
    }

    m_stateManager->getContext()->m_wind->draw(m_quit_level_choose_btn);
}

void LevelChooseState::quitLevelChoose() {
    m_stateManager->switchTo(StateType::MainMenu);
}

void LevelChooseState::choose(int level_id) {
    m_stateManager->getContext()->m_level_manager->setCurrentLevel(level_id);

    m_stateManager->switchTo(StateType::Level);
}
