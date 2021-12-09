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
        renderer.setView(m_simulation_view);

        for (auto &component: m_components) {
            component->render(renderer);
        }

        renderer.setView(renderer.getDefaultView());
    }

    bool Simulation::handleEvent(Event e) {
        if (e.type == sf::Event::KeyPressed) {
            const float ZOOM_FACTOR = 0.95;
            const float MOVE_FACTOR = 5;

            switch (e.key.code) {
                case sf::Keyboard::E:
                    m_simulation_view.zoom(ZOOM_FACTOR);
                    break;
                case sf::Keyboard::Q:
                    m_simulation_view.zoom(1 / ZOOM_FACTOR);
                    break;
                case sf::Keyboard::A:
                    m_simulation_view.move(-MOVE_FACTOR, 0);
                    break;
                case sf::Keyboard::S:
                    m_simulation_view.move(0, MOVE_FACTOR);
                    break;
                case sf::Keyboard::D:
                    m_simulation_view.move(MOVE_FACTOR, 0);
                    break;
                case sf::Keyboard::W:
                    m_simulation_view.move(0, -MOVE_FACTOR);
                    break;
            }

            return true;
        }

        for (auto i = m_components.rbegin(); i != m_components.rend(); ++i) {
            if (i->get()->handleEvent(e))
                return true;
        }

        return false;
    }

    Connector *Simulation::tryToConnectWire(Connector *connector, const sf::Vector2f &position) {
        for (auto &component: m_components) {
            Connector *c = component->checkIfCanConnectWire(connector, position);

            if (c != nullptr)
                return c;
        }

        return nullptr;
    }
}