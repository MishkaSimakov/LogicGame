#ifndef LOGICGAMEENGINE_CONNECTOR_H
#define LOGICGAMEENGINE_CONNECTOR_H

#include "Widget.h"
#include "cmath"

namespace gui {
    class ActingLogicalComponent;

    class Connector : public Widget {
    public:
        Connector(ActingLogicalComponent *component, bool type, int id);

        bool handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void render(sf::RenderTarget &renderer) override;

        bool canConnectWire(const sf::Vector2f &position);

        void redraw();

        enum type {
            INPUT = 0,
            OUTPUT = 1
        };

        bool m_is_dragging_wire = false;
        ActingLogicalComponent *m_component;

    protected:
        void redrawConnector();

        void redrawWire();

        bool m_type;
        int m_id;

        Connector *m_connection = nullptr;
        sf::Vector2f m_temp_wire_end_position;

        sf::CircleShape m_shape;
        sf::VertexArray m_wire;
    };
}

#endif //LOGICGAMEENGINE_CONNECTOR_H
