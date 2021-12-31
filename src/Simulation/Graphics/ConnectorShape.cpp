#include "ConnectorShape.h"
#include "WireShape.h"

void ConnectorShape::update() {
    if (m_is_simulation_connector) {
        m_radius += 10.f;
    }

    m_shape.setOrigin(m_radius, m_radius);

    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_is_simulation_connector ? sf::Color::Green : sf::Color::Red);

    m_shape.setPosition(m_position);

    for (auto wire: m_connected_wires) {
        wire->update();
    }
}

void ConnectorShape::draw(Window *window) {
    window->draw(m_shape);
}

bool ConnectorShape::checkClick(const sf::Vector2f &position) {
    return m_shape.getGlobalBounds().contains(position);
}

void ConnectorShape::removeConnection(WireShape *wire) {
    auto itr = std::find(m_connected_wires.begin(), m_connected_wires.end(), wire);

    if (itr == m_connected_wires.end()) return;

    m_connected_wires.erase(itr);
}

void ConnectorShape::addConnection(WireShape *wire) {
    m_connected_wires.push_back(wire);
}
