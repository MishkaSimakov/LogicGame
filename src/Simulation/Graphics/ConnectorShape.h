#ifndef LOGICGAMEENGINE_CONNECTORSHAPE_H
#define LOGICGAMEENGINE_CONNECTORSHAPE_H

#include "Window.h"
#include "Colors.h"
#include "Constants/Paths.h"
#include "Constants/Colors.h"

#include <map>
#include <SFML/Graphics.hpp>

class Connector;

class WireShape;

enum class ConnectorType {
    INPUT,
    OUTPUT,
    SIMULATION_INPUT,
    SIMULATION_OUTPUT
};

class ConnectorShape {
public:
    explicit ConnectorShape(Connector *connector, ConnectorType type, bool *value_link) :
            m_connector(connector),
            m_type(type),
            m_value_link(value_link) {};

    void update();

    void draw(Window *window);

    bool checkClick(const sf::Vector2f &position);

    const sf::Vector2f &getPosition() const {
        return m_position;
    }

    void addConnection(WireShape *wire);

    void removeConnection(WireShape *wire);

    std::vector<WireShape *> &getConnections() {
        return m_connected_wires;
    }

    void setPosition(const sf::Vector2f &position) {
        m_position = position;
        update();
    }

    void setLabel(const std::wstring &label) {
        m_label = label;
    };

    Connector *getConnector() const {
        return m_connector;
    }

    bool getValue() const {
        return m_value_link != nullptr && *m_value_link;
    }

protected:
    Connector *m_connector;

    std::map<ConnectorType, float> m_radius{
            {ConnectorType::INPUT,             10.f},
            {ConnectorType::OUTPUT,            10.f},
            {ConnectorType::SIMULATION_INPUT,  20.f},
            {ConnectorType::SIMULATION_OUTPUT, 20.f},
    };

    sf::Vector2f m_position;
    sf::CircleShape m_shape;
    sf::Text m_label_shape;
    sf::RectangleShape m_label_background_shape;

    std::wstring m_label;

    std::vector<WireShape *> m_connected_wires;

    ConnectorType m_type;

    bool *m_value_link;
};


#endif //LOGICGAMEENGINE_CONNECTORSHAPE_H
