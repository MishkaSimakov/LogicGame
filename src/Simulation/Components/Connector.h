#ifndef LOGICGAMEENGINE_CONNECTOR_H
#define LOGICGAMEENGINE_CONNECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "ConnectorShape.h"

class Connector {
public:
    enum class Type {
        INPUT = 0,
        OUTPUT
    };

    explicit Connector(Type type) : m_type(type), m_shape(this) {};

    void addConnection(const Connector *connector);
    void removeConnection(const Connector *connector);

    bool canConnectWire(const Connector *connector);
    bool canProduceWire();

    Type getType() const {
        return m_type;
    }

    bool getValue() const {
        return m_value;
    };

    void setValue(bool value) {
        m_value = value;
    }

    ConnectorShape *getShape() {
        return &m_shape;
    }

protected:
    Type m_type;
    bool m_value {false};

    ConnectorShape m_shape;

    std::vector<const Connector *> m_connections;
};

#endif //LOGICGAMEENGINE_CONNECTOR_H
