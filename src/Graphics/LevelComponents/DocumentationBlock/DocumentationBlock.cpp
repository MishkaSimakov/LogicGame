#include "DocumentationBlock.h"
#include "StateManager.h"

DocumentationBlock::DocumentationBlock(
        const Level &level,
        const LevelLayout &layout,
        SharedContext *sharedContext
) :
        m_shared_context(sharedContext),
        m_background(
                layout.documentation_block.getSize(), layout.border_radius,
                RoundedRectangle::BOTTOM_RIGHT | RoundedRectangle::TOP_RIGHT
        ),
        m_title(level.getTitle(), ResourceHolder::get().fonts.get("arial"),
                layout.documentation_block_title.getFontSize()),
        m_documentation(layout.documentation_block.width, level, layout.documentation_block_description),
        m_description_scroll_box(sharedContext, StateType::Level, &m_documentation),
        m_hide_btn(sharedContext, StateType::Level, {40, 40}),
        m_show_btn(sharedContext, StateType::Level, {40, 40}),
        m_layout(layout) {
    m_title.setStyle(sf::Text::Bold);
    m_title.setFillColor(sf::Color::Black);

    m_background.setFillColor(sf::Color(220, 220, 220));
    m_background.setOutlineColor(sf::Color(240, 240, 240));
    m_background.setOutlineThickness(1);

    m_show_btn.setVisible(false);
    m_show_btn.setOnClickCallback(&DocumentationBlock::show, this);
    m_show_btn.setTexture(&ResourceHolder::get().textures.get("icons/menu_2"));
    m_show_btn.setPosition({m_layout.offset.x * 2 + 40, m_layout.offset.y});

    m_hide_btn.setOnClickCallback(&DocumentationBlock::hide, this);
    m_hide_btn.setTexture(&ResourceHolder::get().textures.get("icons/X_simple_2"));

    m_description_scroll_box.setMaxHeight(
            (float) m_shared_context->m_wind->getWindowSize().y - layout.offset.y * 2 - m_title.getGlobalBounds().height
    );

    updatePositions();
}

void DocumentationBlock::draw() {
    if (m_animation_offset.x + m_layout.documentation_block.width > 0) {
        m_shared_context->m_wind->draw(m_background);
        m_shared_context->m_wind->draw(m_title);
        m_shared_context->m_wind->draw(m_description_scroll_box);

        m_shared_context->m_wind->draw(m_hide_btn);
    } else {
        m_shared_context->m_wind->draw(m_show_btn);
    }
}

void DocumentationBlock::show() {
    m_show_btn.setVisible(false);
    m_hide_btn.setVisible(true);

    m_state = State::OPENING;
}

void DocumentationBlock::hide() {
    m_state = State::CLOSING;
}

void DocumentationBlock::update(const sf::Time &time) {
    if (m_state == State::FIXED) return;

    m_animation_time += time.asMilliseconds();

    if (m_state == State::OPENING) {
        m_animation_offset.x = easeInOut(-m_layout.documentation_block.width, 0, (float) m_animation_time / 500);

        if (m_animation_offset.x == 0) { // fully opened
            m_state = State::FIXED;
            m_animation_time = 0;
        }
    } else { // m_state == State::CLOSING
        m_animation_offset.x = easeInOut(0, -m_layout.documentation_block.width, (float) m_animation_time / 500);

        if (m_animation_offset.x == -m_layout.documentation_block.width) { // fully closed
            m_state = State::FIXED;
            m_animation_time = 0;

            m_show_btn.setVisible(true);
            m_hide_btn.setVisible(false);
        }
    }

    updatePositions();
}

void DocumentationBlock::updatePositions() {
    m_hide_btn.setPosition(
            sf::Vector2f(
                    m_layout.documentation_block.width - m_hide_btn.getSize().x - m_layout.offset.x,
                    m_layout.offset.y
            ) + m_animation_offset
    );

    m_background.setPosition(m_layout.documentation_block.getPosition() + m_animation_offset);

    m_title.setPosition(
            m_layout.documentation_block_title.getPosition(m_title.getGlobalBounds().width)
            + m_animation_offset
    );
    m_documentation.setPosition(
            m_layout.documentation_block_description.getPosition(m_documentation.getGlobalBounds().width)
            + m_animation_offset
    );

    m_description_scroll_box.setInnerContent(&m_documentation);
}

DocumentationBlock::State DocumentationBlock::getState() const {
    return m_state;
}

float DocumentationBlock::getPosition() const {
    return m_animation_offset.x + m_layout.documentation_block.width;
}

void DocumentationBlock::setLevel(const Level &level) {
    m_title.setString(level.getTitle());
    m_documentation.setLevel(level);

    updatePositions();
}
