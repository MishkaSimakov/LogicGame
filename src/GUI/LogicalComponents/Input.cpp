#include "Input.h"
#include "ActingLogicalComponent.h"
#include <iostream>

namespace gui {
    Input::Input(ActingLogicalComponent *component, int id) : m_id(id) {
        m_shape.setRadius(5);
        m_shape.setFillColor(sf::Color::Magenta); // TODO: change to gui::colors
        m_shape.setOutlineThickness(1);
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setOrigin(5, 5);

        redraw(component);
    }

    void Input::render(sf::RenderTarget &renderer) {
        renderer.draw(m_shape);
    }

    void Input::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        //
    }

    void Input::redraw(ActingLogicalComponent *component) {
        m_shape.setPosition(
                component->getSize().x / (float) (component->getInputsCount() + 1) * (float) (m_id + 1) +
                component->getPosition().x,
                component->getPosition().y + component->getSize().y
        );
    }
}