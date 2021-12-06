#include "StaticLogicalComponent.h"

namespace gui {
    StaticLogicalComponent::StaticLogicalComponent(const sf::Vector2f &position, const std::string &texture)
            : m_component({70, 70}) {
        m_component.setTexture(&ResourceHolder::get().textures.get(texture));
        m_component.setPosition(position);
    }

    bool StaticLogicalComponent::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f pos(sf::Mouse::getPosition(window));

            if (m_component.getGlobalBounds().contains(pos.x, pos.y)) {
                gui::Simulation::get()->addLogicalComponent<ActingLogicalComponent>(pos, "LogicalComponents/and", true);

                return true;
            }
        }

        return false;
    }

    void StaticLogicalComponent::render(sf::RenderTarget &renderer) {
        renderer.draw(m_component);
    }
}
