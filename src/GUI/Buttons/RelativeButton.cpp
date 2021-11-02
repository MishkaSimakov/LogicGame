#include "RelativeButton.h"

namespace gui {
    RelativeButton::RelativeButton(sf::Vector2f pos, sf::Vector2f btn_size, const std::string &text,
                                   const sf::RenderWindow &window) :
            m_position(pos), m_size(btn_size) {
        setText(text);
        recalculate(window);
    }

    void RelativeButton::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        Button::handleEvent(e, window);

        if (e.type == sf::Event::Resized)
            recalculate(window);
    }

    void RelativeButton::recalculate(const sf::RenderWindow &window) {
        float width = window.getSize().x;
        float height = window.getSize().y;

        setSize({width * m_size.x, height * m_size.y});
        setPosition(
                {
                        width * m_position.x - m_button.getGlobalBounds().width / 2,
                        height * m_position.y - m_button.getGlobalBounds().height / 2
                });
    }
}
