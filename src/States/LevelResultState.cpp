#include "LevelResultState.h"

LevelResultState::LevelResultState(StateManager *stateManager) :
        BaseState(stateManager, true),
        m_background(m_size, 18.f),
        m_close_btn(stateManager->getContext(), StateType::LevelResult, m_close_btn_size),
        m_next_level_btn(stateManager->getContext(), StateType::LevelResult, m_next_level_btn_size) {

    m_result_messages[LevelManager::LevelResult::SUCCESS] = L"Поздравляем!\nВы справились с этим заданием.";
    m_result_messages[LevelManager::LevelResult::PARTIALLY_WRONG] = L"Что-то не так.\nПодумайте ещё...";
    m_result_messages[LevelManager::LevelResult::TOTALLY_WRONG] = L"Подумайте ещё...";

    m_position = ((sf::Vector2f) m_stateManager->getContext()->m_wind->getWindowSize() - m_size) / 2.f;

    m_message.setFont(ResourceHolder::get().fonts.get("arial"));
    m_message.setPosition(m_position + m_offset);
    m_message.setCharacterSize(30);
    m_message.setFillColor(sf::Color::Black);

    m_submessage.setFont(ResourceHolder::get().fonts.get("arial"));
    m_submessage.setCharacterSize(25);
    m_submessage.setFillColor(sf::Color(0, 0, 0, 100));

    m_fade_effect.setPosition({0, 0});
    m_fade_effect.setSize((sf::Vector2f) m_stateManager->getContext()->m_wind->getWindowSize());
    m_fade_effect.setFillColor(sf::Color(0, 0, 0, 100));
    m_fade_effect.setOutlineThickness(0);

    m_background.setPosition(m_position);
    m_background.setFillColor(sf::Color(220, 220, 220));

    m_message.setPosition(m_position + m_offset);
    m_message.setCharacterSize(30);
    m_message.setFont(ResourceHolder::get().fonts.get("arial"));
    m_message.setFillColor(sf::Color::Black);

    m_close_btn.setVisible(false);
    m_close_btn.setString(L"Закрыть");
    m_close_btn.setPosition({
                                    m_position.x + m_offset.x,
                                    m_position.y + m_size.y - m_offset.y - m_close_btn_size.y
                            });
    m_close_btn.setOnClickCallback(&LevelResultState::hide, this);

    m_next_level_btn.setVisible(false);
    m_next_level_btn.setString(L"Следующий уровень");
    m_next_level_btn.setPosition(
            {
                    m_position.x + m_size.x - m_offset.x - m_next_level_btn_size.x,
                    m_position.y + m_size.y - m_offset.y - m_next_level_btn_size.y
            }
    );
    m_next_level_btn.setOnClickCallback(&LevelResultState::nextLevel, this);
}

void LevelResultState::onCreate() {
}

void LevelResultState::onDestroy() {

}

void LevelResultState::activate() {
    LevelManager *levelManager = m_stateManager->getContext()->m_level_manager;

    m_message.setString(m_result_messages[levelManager->getResult()]);

    m_submessage.setString(
            L"Вы прошли " + std::to_wstring(levelManager->getPassedTestsCount()) +
            L" из " + std::to_wstring(levelManager->getCurrentLevel()->getTests().size()) + L" тестов"
    );
    m_submessage.setPosition(
            {
                    m_position.x + m_offset.x,
                    m_position.y + 2 * m_offset.y + m_message.getGlobalBounds().height
            }
    );

    m_close_btn.setVisible(true);

    m_next_level_btn.setVisible(true);
    m_next_level_btn.setEnabled(levelManager->isCurrentLevelPassed());
}

void LevelResultState::deactivate() {
    m_close_btn.setVisible(false);
    m_next_level_btn.setVisible(false);
}

void LevelResultState::update(const sf::Time &time) {

}

void LevelResultState::draw() {
    m_stateManager->getContext()->m_wind->draw(m_fade_effect);
    m_stateManager->getContext()->m_wind->draw(m_background);
    m_stateManager->getContext()->m_wind->draw(m_message);
    m_stateManager->getContext()->m_wind->draw(m_submessage);
    m_stateManager->getContext()->m_wind->draw(m_close_btn);

    m_stateManager->getContext()->m_wind->draw(m_next_level_btn);
}

void LevelResultState::hide() {
    m_stateManager->switchTo(StateType::Level);
}

void LevelResultState::nextLevel() {
    if (m_stateManager->getContext()->m_level_manager->hasNextLevel()) {
        m_stateManager->getContext()->m_level_manager->nextLevel();
        m_stateManager->switchTo(StateType::Level);
    } else {
        m_stateManager->switchTo(StateType::GameComplete);
    }
}
