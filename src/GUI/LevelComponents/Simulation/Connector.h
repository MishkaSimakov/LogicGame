#ifndef LOGICGAMEENGINE_CONNECTOR_H
#define LOGICGAMEENGINE_CONNECTOR_H

#include "Widget.h"
#include "cmath"
#include "Simulation.h"

namespace gui {
    class Connector : public Widget {
    public:
        Connector(const sf::Vector2f &position, int type);

        bool handleEvent(Event e) override;

        void render(sf::RenderTarget &renderer) override;

        bool canConnectWire(const sf::Vector2f &position);

        void redraw();

        void setPosition(const sf::Vector2f &position) {
            m_position = position;
            redraw();
        }

        void setConnection(Connector *connection) {
            m_connection = connection;
        }

        int getType() const {
            return m_type;
        }

        enum type {
            INPUT = 0,
            OUTPUT = 1
        };

        bool m_is_dragging_wire = false;
    protected:
        void redrawWire();

        int m_type;

        sf::Vector2f m_position;

        Connector *m_connection = nullptr;
        sf::Vector2f m_temp_wire_end_position;

        sf::CircleShape m_shape;
        sf::VertexArray m_wire;
    };
}

#endif //LOGICGAMEENGINE_CONNECTOR_H
