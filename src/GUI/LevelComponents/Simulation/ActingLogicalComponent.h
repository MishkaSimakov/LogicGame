#ifndef LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
#define LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H

#include "Widget.h"
#include "Colors.h"
#include "Connector.h"
#include "ResourceHolder.h"

#include <memory>
#include <string>
#include <vector>
#include "BaseLogicalComponent.h"

namespace gui {
    class ActingLogicalComponent : public Widget {
    public:
        ActingLogicalComponent(
                const sf::Vector2f &position,
                const BaseLogicalComponent &logical_component_data,
                bool is_dragged
        );

        bool handleEvent(Event e) override;

        void render(sf::RenderTarget &renderer) override;

        Connector *checkIfCanConnectWire(Connector *connector, const sf::Vector2f &position);

    protected:
        void redraw();

        sf::Vector2f getConnectorPosition(int connector_id, int connector_type) const;

        sf::Vector2f m_size;
        sf::Vector2f m_position;

        bool m_is_dragged;
        sf::Vector2f m_dragging_origin;

        // shapes
        sf::RectangleShape m_component;

        // inputs
        std::vector<std::unique_ptr<Connector>> m_inputs;

        // outputs
        std::vector<std::unique_ptr<Connector>> m_outputs;

        // Logical component data
        const BaseLogicalComponent m_logical_component_data;
    };
}

#endif //LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
