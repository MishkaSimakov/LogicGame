#include "Simulation.h"

namespace gui {

    Simulation::Simulation() {
        m_static_components.emplace_back(
                sf::Vector2f(500, 500),
                "hello world",
                &m_acting_components
        );
    }

    void Simulation::render(sf::RenderTarget &renderer) {
        for (auto &static_component: m_static_components) {
            static_component.render(renderer);
        }
        for (auto &acting_component: m_acting_components) {
            acting_component.render(renderer);
        }
    }

    void Simulation::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        for (auto &static_component: m_static_components) {
            static_component.handleEvent(e, window);
        }
        for (auto &acting_component: m_acting_components) {
            acting_component.handleEvent(e, window);
        }
    }
}