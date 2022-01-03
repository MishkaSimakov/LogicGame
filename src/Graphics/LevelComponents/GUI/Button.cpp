#include "Button.h"

#include <utility>
#include "StateManager.h"

Button::Button(SharedContext *sharedContext, const sf::Vector2f &size, const sf::Vector2f &position,
               std::wstring string, StateType stateType) :
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

    ButtonStyle regularStyle{
            20, sf::Color::Black, 2,
            sf::Color(200, 200, 200), sf::Color::Black
    };
    ButtonStyle hoverStyle{
            25, sf::Color::Black, 2,
            sf::Color(210, 210, 210), sf::Color::Black
    };
    ButtonStyle activeStyle{
            25, sf::Color::Black, 2,
            sf::Color(220, 220, 220), sf::Color::Black
    };

    m_state_styles[(int) State::REGULAR] = regularStyle;
    m_state_styles[(int) State::HOVER] = hoverStyle;
    m_state_styles[(int) State::ACTIVE] = activeStyle;

    m_label.setFont(ResourceHolder::get().fonts.get("arial"));

    update();
}

void Button::setString(const std::wstring &string) {
    m_string = string;
}

void Button::setSize(const sf::Vector2f &size) {
    m_size = size;
}

void Button::setFontSize(float font_size) {
}

void Button::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

void Button::onClick() {
    std::cout << "click!" << std::endl;
}

void Button::handleMouseMove(const sf::Event &event) {
    sf::Vector2f mouse_pos{sf::Mouse::getPosition(
            *m_shared_context->m_wind->getRenderWindow()
    )};

    if (m_background.getGlobalBounds().contains(mouse_pos)) {
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
    if (m_current_state == State::HOVER) {
        m_current_state = State::ACTIVE;
        update();
    }
}

void Button::handleMouseButtonReleased(const sf::Event &event) {
    if (m_current_state == State::ACTIVE) {
        sf::Vector2f mouse_pos{sf::Mouse::getPosition(
                *m_shared_context->m_wind->getRenderWindow()
        )};

        if (m_background.getGlobalBounds().contains(mouse_pos)) {
            onClick();
            m_current_state = State::HOVER;
        } else {
            m_current_state = State::REGULAR;
        }

        update();
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_background);

    if (!m_string.empty())
        target.draw(m_label);
}

void Button::update() {
    m_background.setPosition(m_position);
    m_background.setFillColor(m_state_styles[(int) m_current_state].fill_color);
    m_background.setOutlineColor(m_state_styles[(int) m_current_state].outline_color);
    m_background.setOutlineThickness(m_state_styles[(int) m_current_state].outline_thickness);

    m_label.setString(m_string);
    m_label.setCharacterSize(m_state_styles[(int) m_current_state].font_size);
    m_label.setFillColor(m_state_styles[(int) m_current_state].font_color);
    m_label.setPosition(getLabelPosition());
}

sf::Vector2f Button::getLabelPosition() {
    sf::Vector2f offset{
            (m_background.getGlobalBounds().width - m_label.getGlobalBounds().width) / 2.f,
            (m_background.getGlobalBounds().height - m_label.getGlobalBounds().height) / 2.f - 5
    };

    return m_background.getPosition() + offset;
}
