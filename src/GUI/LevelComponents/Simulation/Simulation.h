#ifndef LOGICGAMEENGINE_SIMULATION_H
#define LOGICGAMEENGINE_SIMULATION_H

#include "Widget.h"

#include <memory>
#include <vector>

namespace gui {
    class Connector;

    class ActingLogicalComponent;

    class Simulation : public Widget {
    public:
        static Simulation *get();

        void reset();

        template<typename... Args>
        void addLogicalComponent(Args &&... args);

        bool handleEvent(Event e) override;

        void render(sf::RenderTarget &renderer) override;

        Connector *tryToConnectWire(Connector *connector, const sf::Vector2f &position);

        std::vector<std::unique_ptr<ActingLogicalComponent>> m_components;

        bool need_to_reset{false};

        sf::View m_simulation_view;

        void addSimulationInput(std::unique_ptr<Connector> connector) {
            m_simulation_inputs.push_back(std::move(connector));
        };

        void addSimulationOutput(std::unique_ptr<Connector> connector) {
            m_simulation_outputs.push_back(std::move(connector));
        }

        void runSimulation(std::vector<bool> &input_data, std::vector<bool> &result);
    protected:
        Simulation() : m_simulation_view(sf::FloatRect(0., 0., 1280., 720.)) {        };

        void runSimulationTick();

        std::vector<std::unique_ptr<Connector>> m_simulation_inputs;
        std::vector<std::unique_ptr<Connector>> m_simulation_outputs;
    };

    template<typename... Args>
    void Simulation::addLogicalComponent(Args &&... args) {
        m_components.emplace_back(
                std::make_unique<ActingLogicalComponent>(std::forward<Args>(args)...)
        );
    }
}


#endif //LOGICGAMEENGINE_SIMULATION_H
