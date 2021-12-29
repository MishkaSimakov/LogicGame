#include "Connector.h"

void Connector::removeConnection(const Connector *connector) {
    auto itr = std::find(m_connections.begin(), m_connections.end(), connector);

    if (itr == m_connections.end()) return;

    m_connections.erase(itr);
}

void Connector::addConnection(const Connector *connector) {
    m_connections.push_back(connector);
}

bool Connector::canConnectWire(const Connector *connector) {
    return (m_type == Type::INPUT && connector->getType() == Type::OUTPUT && m_connections.empty()) ||
            (m_type == Type::OUTPUT && connector->getType() == Type::INPUT);
}

bool Connector::canProduceWire() {
    return (m_type == Type::OUTPUT) || (m_type == Type::INPUT && m_connections.empty());
}
