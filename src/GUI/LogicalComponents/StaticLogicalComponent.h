#ifndef LOGICALCOMPONENT_H
#define LOGICALCOMPONENT_H

#include "Widget.h"
#include "Colors.h"
#include "Simulation.h"
#include "ActingLogicalComponent.h"

#include <vector>
#include "ResourceHolder.h"

namespace gui {
    class StaticLogicalComponent : Widget {
    public:
        StaticLogicalComponent(const sf::Vector2f &position, const std::string &texture);

        bool handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void render(sf::RenderTarget &renderer) override;

    protected:
        sf::RectangleShape m_component;
    };
}

#endif // LOGICALCOMPONENT_H
