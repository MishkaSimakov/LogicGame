#include "LevelResultState.h"

LevelResultState::LevelResultState(StateManager *stateManager) :
        BaseState(stateManager, true),
        m_background(m_size, 18.f),
        m_close_btn(stateManager->getContext(), StateType::LevelResult, m_close_btn_size) {

    m_position = ((sf::Vector2f) m_stateManager->getContext()->m_wind->getWindowSize() - m_size) / 2.f;

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

    m_stateManager->getContext()->m_eventManager->addKeyReleasedCallback(
            StateType::LevelResult, sf::Keyboard::Space,
            &LevelResultState::handleSpaceRelease, this
    );
}

void LevelResultState::onCreate() {

}

void LevelResultState::onDestroy() {

}

void LevelResultState::activate() {
    m_close_btn.setVisible(true);
}

void LevelResultState::deactivate() {
    m_close_btn.setVisible(false);
}

void LevelResultState::update(const sf::Time &time) {

}

void LevelResultState::draw() {
    m_stateManager->getContext()->m_wind->draw(m_fade_effect);
    m_stateManager->getContext()->m_wind->draw(m_background);
    m_stateManager->getContext()->m_wind->draw(m_message);
    m_stateManager->getContext()->m_wind->draw(m_close_btn);
}

void LevelResultState::hide() {
    m_stateManager->switchTo(StateType::Level);
}

void LevelResultState::handleSpaceRelease(const sf::Event &event) {
    hide();
}

//    m_is_opened = true;
//    m_result = result;
//    m_close_btn.setVisible(true);
//
//    if (result == LevelResult::SUCCESS) {
//        m_message.setString(L"Поздравляю! Вы справились!");
//    } else if (result == LevelResult::PARTIALLY_WRONG) {
//        m_message.setString(L"Что-то не так!");
//    } else {
//        m_message.setString(L"У вас всё абсолютно неверно. Лучше выключите эту игру.");
//    }
