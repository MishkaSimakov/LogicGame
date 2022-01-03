#include "LevelResultWindow.h"
#include "ResourceHolder.h"

LevelResultWindow::LevelResultWindow(
        SharedContext *sharedContext,
        const sf::Vector2f &size,
        const sf::Vector2f &position
) : m_shared_context(sharedContext), m_size(size), m_position(position), m_background(size, 18.f),
    m_close_btn(tgui::Button::create(L"Закрыть")) {

    m_fade_effect.setPosition({0, 0});
    m_fade_effect.setSize((sf::Vector2f) m_shared_context->m_wind->getWindowSize());
    m_fade_effect.setFillColor(sf::Color(0, 0, 0, 100));
    m_fade_effect.setOutlineThickness(0);

    m_background.setPosition(position);
    m_background.setFillColor(sf::Color(220, 220, 220));

    m_message.setPosition(m_position + m_offset);
    m_message.setCharacterSize(30);
    m_message.setFont(ResourceHolder::get().fonts.get("arial"));
    m_message.setFillColor(sf::Color::Black);

    m_close_btn->setVisible(false);
    m_close_btn->setSize(150, 50);
    m_close_btn->setPosition(m_position.x + m_offset.x, m_position.y + m_size.y - m_offset.y - 50);
    m_close_btn->onClick(&LevelResultWindow::hide, this);
    m_shared_context->m_wind->getGui()->add(m_close_btn);
}

void LevelResultWindow::showWithResult(LevelResultWindow::LevelResult result) {
    m_is_opened = true;
    m_result = result;
    m_close_btn->setVisible(true);

    if (result == LevelResult::SUCCESS) {
        m_message.setString(L"Поздравляю! Вы справились!");
    } else if (result == LevelResult::PARTIALLY_WRONG) {
        m_message.setString(L"Что-то не так!");
    } else {
        m_message.setString(L"У вас всё абсолютно неверно. Лучше выключите эту игру.");
    }
}

void LevelResultWindow::draw() {
    if (m_is_opened) {
        m_shared_context->m_wind->draw(m_fade_effect);
        m_shared_context->m_wind->draw(m_background);
        m_shared_context->m_wind->draw(m_message);
    }
}

void LevelResultWindow::hide() {
    m_is_opened = false;
    m_close_btn->setVisible(false);
}
