#include "StaticLogicalComponent.h"

namespace gui {
    StaticLogicalComponent::StaticLogicalComponent(const sf::Vector2f &position, const std::string &name,
                                                   std::vector<ActingLogicalComponent> *acting_components_list) :
            m_acting_components_list(acting_components_list), m_component({70, 70}) {
        m_component.setOutlineThickness(2);
        m_component.setOutlineColor(gui::colors::dark_primary);
        m_component.setFillColor(gui::colors::primary);
        m_component.setPosition(position);
    }

    void StaticLogicalComponent::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos(sf::Mouse::getPosition(window));

            if (m_component.getGlobalBounds().contains(pos.x, pos.y)) {
                m_acting_components_list->emplace_back(
                        pos,
                        "xor",
                        true
                );
            }
        }
    }

    void StaticLogicalComponent::render(sf::RenderTarget &renderer) {
        renderer.draw(m_component);
    }
}
