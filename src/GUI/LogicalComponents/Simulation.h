#ifndef LOGICGAMEENGINE_SIMULATION_H
#define LOGICGAMEENGINE_SIMULATION_H

#include "Widget.h"
#include <memory>
#include "ActingLogicalComponent.h"
#include "Wire.h"
#include <vector>

namespace gui {
    class Simulation : public Widget {
    public:
        Simulation() = default;

        template<typename T, typename... Args>
        void addLogicalComponent(Args &&... args);

        void addLogicalComponent(std::unique_ptr<ActingLogicalComponent> component);

        void handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void render(sf::RenderTarget &renderer) override;

        std::vector<std::unique_ptr<ActingLogicalComponent>> m_components;
        std::vector<Wire> m_wires;
    };

    template<typename T, typename... Args>
    void Simulation::addLogicalComponent(Args &&... args) {
        addLogicalComponent(std::make_unique<T>(std::forward<Args>(args)...));
    }
}


#endif //LOGICGAMEENGINE_SIMULATION_H
