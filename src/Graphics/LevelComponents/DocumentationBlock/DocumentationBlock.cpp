#include "DocumentationBlock.h"
#include "StateManager.h"

DocumentationBlock::DocumentationBlock(
        const std::wstring &title, const std::wstring &description,
        const sf::Vector2f &size, SharedContext *sharedContext
) :
        m_background(
                size, 18,
                RoundedRectangle::BOTTOM_RIGHT | RoundedRectangle::TOP_RIGHT
        ),
        m_title(m_offset, size.x - m_offset.x * 2, title, 40, "arial", sf::Text::Bold),
        m_description({m_offset.x, 75}, size.x - m_offset.x * 2, description, 30),
        m_shared_context(sharedContext),
        m_hide_btn(sharedContext, StateType::Level, {40, 40}),
        m_show_btn(sharedContext, StateType::Level, {40, 40}),
        m_position(size.x), m_opened_position(size.x) {
    m_background.setPosition(0, 0);
    m_background.setFillColor(sf::Color(220, 220, 220));
    m_background.setOutlineColor(sf::Color(240, 240, 240));
    m_background.setOutlineThickness(1);

    m_show_btn.setVisible(false);
    m_show_btn.setOnClickCallback(&DocumentationBlock::show, this);
    m_show_btn.setTexture(&ResourceHolder::get().textures.get("horizontal_bars"));

    m_hide_btn.setOnClickCallback(&DocumentationBlock::hide, this);
    m_hide_btn.setTexture(&ResourceHolder::get().textures.get("cross"));

    updatePositions();
}

void DocumentationBlock::draw() {
    if (m_position > 0) {
        m_shared_context->m_wind->draw(m_background);
        m_shared_context->m_wind->draw(m_title);
        m_shared_context->m_wind->draw(m_description);

        m_shared_context->m_wind->draw(m_hide_btn);
    }

    m_shared_context->m_wind->draw(m_show_btn);
}

void DocumentationBlock::show() {
    m_show_btn.setVisible(false);
    m_state = State::OPENING;
}

void DocumentationBlock::hide() {
    m_state = State::CLOSING;
}

void DocumentationBlock::update(const sf::Time &time) {
    if (m_state == State::FIXED) return;

    m_animation_time += time.asMilliseconds();

    if (m_state == State::OPENING) {
        m_position = easeInOut(0, m_opened_position, (float) m_animation_time / 500);

        if (m_position == m_opened_position) {
            m_state = State::FIXED;
            m_animation_time = 0;

            m_hide_btn.setEnabled(true);
            m_show_btn.setEnabled(false);
        }
    } else { // m_state == State::FIXED
        m_position = easeInOut(m_opened_position, 0, (float) m_animation_time / 500);

        if (m_position == 0) {
            m_state = State::FIXED;
            m_animation_time = 0;

            m_show_btn.setVisible(true);
            m_hide_btn.setEnabled(false);
            m_show_btn.setEnabled(true);
        }
    }

    updatePositions();
}

void DocumentationBlock::updatePositions() {
    m_hide_btn.setPosition({m_position - 40 - 25, 25});
    m_show_btn.setPosition({25, 25});

    m_background.setPosition(m_position - m_opened_position, 0);
    m_title.setPosition({m_offset.x + m_position - m_opened_position, m_offset.y});
    m_description.setPosition({m_offset.x + m_position - m_opened_position, 75});
}
