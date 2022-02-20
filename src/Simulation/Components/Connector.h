#ifndef LOGICGAMEENGINE_CONNECTOR_H
#define LOGICGAMEENGINE_CONNECTOR_H

#include "ConnectorShape.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>

class ActingLogicalComponent;

class Connector {
public:
    explicit Connector(ConnectorType type, ActingLogicalComponent *component = nullptr) :
            m_type(type), m_shape(this, type, &m_value), m_component(component) {};

    void addConnection(Connector *connector);

    void removeConnection(Connector *connector);

    bool canConnectWire(const Connector *connector);

    bool canProduceWire();

    ConnectorType getType() const {
        return m_type;
    }

    bool getValue() const {
        return m_value;
    };

    void setValue(bool value) {
        m_value = value;

        m_shape.update();
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

    bool isInput() const {
        return m_type == ConnectorType::INPUT || m_type == ConnectorType::SIMULATION_OUTPUT;
    }

    bool isOutput() const {
        return m_type == ConnectorType::OUTPUT || m_type == ConnectorType::SIMULATION_INPUT;
    }

protected:
    ConnectorType m_type;
    bool m_value{false};

    ConnectorShape m_shape;

    std::vector<Connector *> m_connections;

    ActingLogicalComponent *m_component;
};

#endif //LOGICGAMEENGINE_CONNECTOR_H
