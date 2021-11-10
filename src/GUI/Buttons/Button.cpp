#include "Button.h"

namespace gui {
    Button::Button(
            const sf::Vector2f &position,
            const sf::Vector2f &button_size,
            const std::string &text,
            const sf::Color &text_color,
            const std::string &font,
            unsigned int font_size,
            const sf::Color &color,
            float outline_thickness,
            const sf::Color &outline_color,
            const sf::Color &hover_color,
            const sf::Color &active_color
    ) :
            m_background_color(color),
            m_hover_background_color(hover_color),
            m_active_background_color(active_color) {
        // button background
        m_background.setPosition(position);
        m_background.setSize(button_size);

        updateColor(NORMAL); // set background fill color

        m_background.setOutlineThickness(outline_thickness);
        m_background.setOutlineColor(outline_color);

        // button text
        m_text.setString(text);
        m_text.setFont(ResourceHolder::get().fonts.get(font));
        m_text.setCharacterSize(font_size);
        m_text.setFillColor(text_color);
        m_text.setStyle(sf::Text::Bold);

        updateTextPosition();
    }

    void Button::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        if (e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased || e.type == sf::Event::MouseMoved) {
            sf::Vector2f pos(sf::Mouse::getPosition(window));

            // cursor over button
            if (m_background.getGlobalBounds().contains(pos)) {
                if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
                    // click
                    m_callback();

                    updateColor(NORMAL);
                } else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                    // active
                    updateColor(ACTIVE);
                } else {
                    // hover
                    updateColor(HOVER);
                }

                return;
            }

            // cursor somewhere else
            updateColor(NORMAL);
        }
    }

    void Button::setTexture(const sf::Texture &texture) {
        m_has_texture = true;

        m_background.setFillColor(sf::Color::Transparent);
        m_background.setTexture(&texture);

        updateColor(NORMAL);
    }

    void Button::render(sf::RenderTarget &renderer) {
        renderer.draw(m_background);
        renderer.draw(m_text);
    }

    void Button::setCallback(std::function<void(void)> callback) {
        m_callback = std::move(callback);
    }

    void Button::updateTextPosition() {
        m_text.setOrigin(m_text.getGlobalBounds().width / 2,
                         m_text.getGlobalBounds().height / 2);

        m_text.setPosition(m_background.getPosition().x + m_background.getGlobalBounds().width / 2.0f,
                           m_background.getPosition().y + m_background.getGlobalBounds().height / 2.0f);
    }

    void Button::updateColor(unsigned int state) {
        if (m_has_texture) {
            m_background.setFillColor(sf::Color::White);
            return;
        }

        if (state == NORMAL) {
            m_background.setFillColor(m_background_color);
        } else if (state == HOVER) {
            m_background.setFillColor(m_hover_background_color);
        } else { // ACTIVE state
            m_background.setFillColor(m_active_background_color);
        }
    }
}
