#include "StaticLogicalComponent.h"

namespace gui {
    StaticLogicalComponent::StaticLogicalComponent(const sf::Vector2f &position,
                                                   BaseLogicalComponent logical_component_data)
            : m_component({70, 70}), m_logical_component_data(std::move(logical_component_data)) {
        m_component.setTexture(m_logical_component_data.getTexture());
        m_component.setPosition(position);
    }

    bool StaticLogicalComponent::handleEvent(Event e) {
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos(sf::Mouse::getPosition(e.getRenderTarget()));

            if (m_component.getGlobalBounds().contains(pos.x, pos.y)) {
                gui::Simulation::get()->addLogicalComponent(pos, m_logical_component_data, true);

                return true;
            }
        }

        return false;
    }

    void StaticLogicalComponent::render(sf::RenderTarget &renderer) {
        renderer.draw(m_component);
    }
}
