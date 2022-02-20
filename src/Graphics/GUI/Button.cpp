#include "Button.h"


Button::Button(
        SharedContext *sharedContext, StateType stateType,
        const sf::Vector2f &size, const sf::Vector2f &position,
        std::wstring string, ButtonStyle regular_style, ButtonStyle hover_style, ButtonStyle active_style
) :
        m_shared_context(sharedContext), m_string(std::move(string)), m_position(position), m_size(size),
        m_background(m_size, 5.f) {

    m_shared_context->m_eventManager->addEventCallback(
            stateType, sf::Event::MouseMoved, &Button::handleMouseMove, this
    );
    m_shared_context->m_eventManager->addMousePressedCallback(
            stateType, sf::Mouse::Left, &Button::handleMouseButtonPressed, this
    );
    m_shared_context->m_eventManager->addMouseReleasedCallback(
            stateType, sf::Mouse::Left, &Button::handleMouseButtonReleased, this
    );

    m_state_styles[(int) State::REGULAR] = regular_style;
    m_state_styles[(int) State::HOVER] = hover_style;
    m_state_styles[(int) State::ACTIVE] = active_style;

    m_label.setFont(ResourceHolder::get().fonts.get("arial"));

    update();
}

void Button::setString(const std::wstring &string) {
    m_string = string;
    update();
}

void Button::setPosition(const sf::Vector2f &position) {
    m_position = position;
    update();
}

void Button::handleMouseMove(const sf::Event &event) {
    if (!m_is_visible) return;

    sf::Vector2f mouse_pos{m_shared_context->m_wind->getMousePosition()};

    if (contains(mouse_pos)) {
        if (m_current_state == State::REGULAR) {
            m_current_state = State::HOVER;
            update();
        }
    } else if (m_current_state == State::HOVER) {
        m_current_state = State::REGULAR;
        update();
    }
}

void Button::handleMouseButtonPressed(const sf::Event &event) {
    if (!m_is_visible || !m_is_enabled) return;

    if (m_current_state == State::HOVER) {
        m_current_state = State::ACTIVE;
        update();
    }
}

void Button::handleMouseButtonReleased(const sf::Event &event) {
    if (!m_is_visible || !m_is_enabled) return;

    if (m_current_state == State::ACTIVE) {
        sf::Vector2f mouse_pos{m_shared_context->m_wind->getMousePosition()};

        if (contains(mouse_pos)) {
            m_current_state = State::HOVER;

            if (m_on_click_callback) {
                m_on_click_callback();
            }
        } else {
            m_current_state = State::REGULAR;
        }

        update();
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_is_visible) return;

    if (m_texture) {
        target.draw(m_sprite);

        return;
    }

    target.draw(m_background);

    if (!m_string.empty())
        target.draw(m_label);
}

void Button::update() {
    if (m_current_state == State::HOVER && !m_is_enabled) {
        m_shared_context->m_wind->setMouseCursor(sf::Cursor::NotAllowed);
    } else {
        m_shared_context->m_wind->setMouseCursor(sf::Cursor::Arrow);
    }

    m_background.setPosition(m_position);
    if (m_texture) {
        m_sprite.setTexture(*m_texture);
        m_sprite.setPosition(m_position);

        float scale_factor = std::min(m_size.x / (float) m_texture->getSize().x,
                                      m_size.y / (float) m_texture->getSize().y);
        m_sprite.setScale(scale_factor, scale_factor);

        auto spriteRect = m_sprite.getLocalBounds();
        m_sprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f, spriteRect.top + spriteRect.height / 2.0f);
        m_sprite.setPosition(m_position + m_size / 2.f);

        m_sprite.setColor(m_current_state == State::ACTIVE ? sf::Color(255, 255, 255, 200) : sf::Color::Black);
    } else {
        m_background.setFillColor(m_state_styles[(int) m_current_state].fill_color);

        m_background.setOutlineColor(m_state_styles[(int) m_current_state].outline_color);
        m_background.setOutlineThickness(m_state_styles[(int) m_current_state].outline_thickness);

        m_label.setString(m_string);
        m_label.setCharacterSize(m_state_styles[(int) m_current_state].font_size);
        m_label.setFillColor(m_state_styles[(int) m_current_state].font_color);

        auto textRect = m_label.getLocalBounds();
        m_label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        m_label.setPosition(m_background.getPosition() + m_background.getSize() / 2.f);
    }
}

void Button::setTexture(const sf::Texture *texture) {
    m_texture = texture;
    update();
}

void Button::setVisible(bool is_visible) {
    if (!is_visible)
        m_current_state = State::REGULAR;

    m_is_visible = is_visible;
    update();
}

void Button::setEnabled(bool is_enabled) {
    if (!is_enabled)
        m_current_state = State::REGULAR;

    m_is_enabled = is_enabled;
    update();
}

bool Button::contains(const sf::Vector2f &position) {
    sf::Vector2f offset{10.f, 10.f};
    sf::FloatRect rect{m_position - offset, m_size + offset};

    return rect.contains(position);
}
