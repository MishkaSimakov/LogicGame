#include "Simulation.h"

namespace gui {
    void Simulation::render(sf::RenderTarget &renderer) {
        for (auto &component: m_components) {
            component->render(renderer);
        }
        for (auto &wire: m_wires) {
            wire.render(renderer);
        }
    }

    void Simulation::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        for (auto &component: m_components) {
            component->handleEvent(e, window);
        }
    }

    void Simulation::addLogicalComponent(std::unique_ptr<ActingLogicalComponent> component) {
        m_components.push_back(std::move(component));
    }
}