#include "ActingLogicalComponent.h"

namespace gui {
    ActingLogicalComponent::ActingLogicalComponent(const sf::Vector2f &position, const std::string &name,
                                                   bool is_dragged) :
            m_position(position), m_is_dragged(is_dragged), m_size(25, 25) {
        drawComponent();
    }

    void ActingLogicalComponent::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        if (m_is_dragged) {
            if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
                m_is_dragged = false;
            } else if (e.type == sf::Event::MouseMoved) {
                m_position = sf::Vector2f(sf::Mouse::getPosition(window)) - m_size / 2.f;
            }

            drawComponent();
        } else {
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                auto pos = sf::Mouse::getPosition(window);

                if (m_component.getGlobalBounds().contains((float) pos.x, (float) pos.y)) {
                    m_is_dragged = true;
                    drawComponent();
                }
            }
        }
    }

    void ActingLogicalComponent::render(sf::RenderTarget &renderer) {
        renderer.draw(m_component);
    }

    void ActingLogicalComponent::drawComponent() {
        m_component.setOutlineThickness(2);
        m_component.setOutlineColor(gui::colors::dark_primary);
        m_component.setFillColor(gui::colors::primary + (m_is_dragged ? sf::Color(40, 40, 40) : sf::Color::Black));
        m_component.setSize(m_size);
        m_component.setPosition(m_position);
    }
}
