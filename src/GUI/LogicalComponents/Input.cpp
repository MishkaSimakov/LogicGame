#include "Input.h"
#include "ActingLogicalComponent.h"
#include <iostream>

namespace gui {
    Input::Input(ActingLogicalComponent *component, int id) :
            m_component(component),
            m_id(id) {
        m_shape.setRadius(5);
        m_shape.setFillColor(sf::Color::Magenta); // TODO: change to gui::colors
        m_shape.setOutlineThickness(1);
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setOrigin(5, 5);

        redraw();
    }

    void Input::render(sf::RenderTarget &renderer) {
        renderer.draw(m_shape);
    }

    void Input::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos(sf::Mouse::getPosition(window));

            if (m_shape.getGlobalBounds().contains(pos)) {
//                is_dragged = true;
            }
        }
    }

    void Input::redraw() {
        m_shape.setPosition(
                m_component->getSize().x / (float) (m_component->getInputsCount() + 1) * (float) (m_id + 1) +
                m_component->getPosition().x,
                m_component->getPosition().y + m_component->getSize().y
        );
    }
}