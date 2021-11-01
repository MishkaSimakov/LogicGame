#include "Button.h"

namespace gui {
    Button::Button() {
        m_button.setOutlineThickness(2);
        m_button.setOutlineColor(gui::colors::dark_primary);
        m_button.setFillColor(gui::colors::primary);

        m_text.setFont(ResourceHolder::get().fonts.get("arial"));
        m_text.setCharacterSize(30);
        m_text.setFillColor(gui::colors::white);
        m_text.setStyle(sf::Text::Bold);
    }

    Button::Button(const sf::Vector2f &posision, const sf::Vector2f &button_size, const std::string &text) :
            Button() {
        setSize(button_size);
        setPosition(posision);
        setText(text);
    }

    void Button::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            auto pos = sf::Mouse::getPosition(window);

            if (m_button.getGlobalBounds().contains((float) pos.x, (float) pos.y)) {
                m_callback();
            }
        } else if (e.type == sf::Event::MouseMoved) {
            auto pos = sf::Mouse::getPosition(window);

            if (m_button.getGlobalBounds().contains((float) pos.x, (float) pos.y)) {
                m_button.setFillColor(gui::colors::dark_primary);
            } else {
                m_button.setFillColor(gui::colors::primary);
            }
        }
    }

    void Button::render(sf::RenderTarget &renderer) {
        renderer.draw(m_button);
        renderer.draw(m_text);
    }

    void Button::setPosition(const sf::Vector2f &pos) {
        m_button.setPosition(pos);
        m_text.setPosition(pos);

        updateText();
    }

    void Button::setSize(const sf::Vector2f &button_size) {
        m_button.setSize(button_size);
        updateText();
    }

    void Button::setText(const std::string &text) {
        m_text.setString(text);
        updateText();
    }

    void Button::setCallback(std::function<void(void)> callback) {
        m_callback = callback;
    }

    void Button::updateText() {
        m_text.setOrigin(m_text.getGlobalBounds().width / 2,
                         m_text.getGlobalBounds().height / 2);

        m_text.setPosition(m_button.getPosition().x + m_button.getGlobalBounds().width / 2.0f,
                           m_button.getPosition().y + m_button.getGlobalBounds().height / 2.0f);
    }
}
