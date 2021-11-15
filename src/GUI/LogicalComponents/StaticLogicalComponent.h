#ifndef LOGICALCOMPONENT_H
#define LOGICALCOMPONENT_H

#include "Widget.h"
#include <vector>
#include "Colors.h"
#include "ActingLogicalComponent.h"
#include "Simulation.h"

namespace gui {
    class StaticLogicalComponent : Widget {
    public:
        StaticLogicalComponent(const sf::Vector2f &position, Simulation *simulation);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

    protected:
        sf::RectangleShape m_component;
        Simulation *m_simulation;
    };
}

#endif // LOGICALCOMPONENT_H
