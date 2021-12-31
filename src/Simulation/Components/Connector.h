#ifndef LOGICGAMEENGINE_CONNECTOR_H
#define LOGICGAMEENGINE_CONNECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "ConnectorShape.h"

class ActingLogicalComponent;

class Connector {
public:
    enum class Type {
        INPUT,
        OUTPUT
    };

    explicit Connector(Type type, bool is_simulation_connector = false, ActingLogicalComponent *component = nullptr) :
            m_type(type), m_shape(this, is_simulation_connector), m_component(component) {};

    void addConnection(Connector *connector);

    void removeConnection(Connector *connector);

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

    std::vector<Connector *> &getConnections() {
        return m_connections;
    }

    ActingLogicalComponent *getComponent() const {
        return m_component;
    }

protected:
    Type m_type;
    bool m_value{false};

    ConnectorShape m_shape;

    std::vector<Connector *> m_connections;

    ActingLogicalComponent *m_component;
};

#endif //LOGICGAMEENGINE_CONNECTOR_H
