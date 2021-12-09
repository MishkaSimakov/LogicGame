#ifndef LOGICALCOMPONENT_H
#define LOGICALCOMPONENT_H

#include "Widget.h"
#include "Colors.h"
#include "Simulation.h"
#include "ActingLogicalComponent.h"
#include "ResourceHolder.h"

#include <utility>
#include <vector>

namespace gui {
    class StaticLogicalComponent : Widget {
    public:
        StaticLogicalComponent(const sf::Vector2f &position, BaseLogicalComponent logical_component_data)
                : m_component({70, 70}), m_logical_component_data(std::move(logical_component_data)) {
            m_component.setTexture(m_logical_component_data.getTexture());
            m_component.setPosition(position);
        }

        bool handleEvent(Event e) override {
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos(sf::Mouse::getPosition(e.getRenderTarget()));

                if (m_component.getGlobalBounds().contains(pos.x, pos.y)) {
                    gui::Simulation::get()
                            ->addLogicalComponent<ActingLogicalComponent>(
                                    pos, m_logical_component_data, true
                            );

                    return true;
                }
            }

            return false;
        }

        void render(sf::RenderTarget &renderer) override {
            renderer.draw(m_component);
        }

    protected:
        sf::RectangleShape m_component;
        BaseLogicalComponent m_logical_component_data;
    };
}

#endif // LOGICALCOMPONENT_H
