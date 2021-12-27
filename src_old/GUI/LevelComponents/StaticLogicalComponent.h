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
        StaticLogicalComponent(const sf::Vector2f &position, BaseLogicalComponent logical_component_data);

        bool handleEvent(Event e) override;

        void render(sf::RenderTarget &renderer) override;
    protected:
        sf::RectangleShape m_component;
        BaseLogicalComponent m_logical_component_data;
    };
}

#endif // LOGICALCOMPONENT_H
