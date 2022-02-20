#include "Connector.h"

void Connector::removeConnection(Connector *connector) {
    auto itr = std::find(m_connections.begin(), m_connections.end(), connector);

    if (itr == m_connections.end()) return;

    m_connections.erase(itr);
}

void Connector::addConnection(Connector *connector) {
    m_connections.push_back(connector);
}

bool Connector::canConnectWire(const Connector *connector) {
    return (isInput() && connector->isOutput() && m_connections.empty()) ||
           (isOutput() && connector->isInput());
}

bool Connector::canProduceWire() {
    return isOutput() || (isInput() && m_connections.empty());
}
