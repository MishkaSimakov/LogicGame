#ifndef LOGICGAMEENGINE_SIMULATION_H
#define LOGICGAMEENGINE_SIMULATION_H

#include "Widget.h"
#include "StaticLogicalComponent.h"
#include "ActingLogicalComponent.h"
#include "Wire.h"
#include <vector>

namespace gui {
    class Simulation : public Widget {
    public:
        Simulation();

        void handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void render(sf::RenderTarget &renderer) override;

        std::vector<StaticLogicalComponent> m_static_components;
        std::vector<ActingLogicalComponent> m_acting_components;
        std::vector<Wire> m_wires;
    };
}


#endif //LOGICGAMEENGINE_SIMULATION_H
