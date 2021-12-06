#include "Simulation.h"
#include "ActingLogicalComponent.h"

namespace gui {
    Simulation *Simulation::get() {
        static Simulation simulation;

        if (simulation.need_to_reset) {
            simulation = Simulation();
        }

        return &simulation;
    }

    void Simulation::reset() {
        need_to_reset = true;
    }

    void Simulation::render(sf::RenderTarget &renderer) {
        for (auto &component: m_components) {
            component->render(renderer);
        }
    }

    bool Simulation::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        for (auto i = m_components.rbegin(); i != m_components.rend(); ++i) {
            if (i->get()->handleEvent(e, window))
                return true;
        }

        return false;
    }

    void Simulation::addLogicalComponent(std::unique_ptr<ActingLogicalComponent> component) {
        m_components.push_back(std::move(component));
    }

    Connector *Simulation::tryToConnectWire(Connector *connector, const sf::Vector2f &position) {
        for (auto &component : m_components) {
            Connector *c = component->canConnectWire(connector, position);

            if (c != nullptr)
                return c;
        }

        return nullptr;
    }
}