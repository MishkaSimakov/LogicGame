#ifndef LOGICGAMEENGINE_CONNECTORSHAPE_H
#define LOGICGAMEENGINE_CONNECTORSHAPE_H

#include "Window.h"
#include <SFML/Graphics.hpp>

class Connector;

class WireShape;

class ConnectorShape {
public:
    explicit ConnectorShape(Connector *connector, bool is_simulation_connector) :
            m_connector(connector),
            m_is_simulation_connector(is_simulation_connector) {};

    void update();

    void draw(Window *window);

    bool checkClick(const sf::Vector2f &position);

    const sf::Vector2f &getPosition() const {
        return m_position;
    }

    void addConnection(WireShape *wire);

    void removeConnection(WireShape *wire);

    void setPosition(const sf::Vector2f &position) {
        m_position = position;
        update();
    }

    Connector *getConnector() const {
        return m_connector;
    }

protected:
    float m_radius{10.f};
    sf::Vector2f m_position;
    sf::CircleShape m_shape;

    std::vector<WireShape *> m_connected_wires;

    bool m_is_simulation_connector;

    Connector *m_connector;
};


#endif //LOGICGAMEENGINE_CONNECTORSHAPE_H
