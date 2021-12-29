#ifndef LOGICGAMEENGINE_CONNECTOR_H
#define LOGICGAMEENGINE_CONNECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Connector {
public:
    Connector(const sf::Vector2f &position, int type);

    bool canConnectWire(const sf::Vector2f &position);

    void setConnection(Connector *connection) {
        m_connection = connection;
    }

    int getType() const {
        return m_type;
    }

    bool getValue() const { return m_value; };

    void setValue(bool value);

    enum type {
        INPUT = 0,
        OUTPUT = 1
    };
protected:
    int m_type;

    bool m_value;

    sf::Vector2f m_position;

    Connector *m_connection = nullptr;
};

#endif //LOGICGAMEENGINE_CONNECTOR_H
