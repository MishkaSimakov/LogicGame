#include "ConnectorShape.h"
#include "WireShape.h"
#include "ResourceHolder.h"

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

    m_label_shape.setFillColor(sf::Color::Black);
    m_label_shape.setString(m_label);
    m_label_shape.setFont(ResourceHolder::get().fonts.get("arial"));
    m_label_shape.setCharacterSize(20);
    m_label_shape.setStyle(sf::Text::Bold);

    m_label_shape.setPosition(
            m_position.x - m_label_shape.getGlobalBounds().width / 2.f,
            m_position.y + m_radius + 5
    );

    sf::Vector2f offset {5., 0.f};
    m_label_background_shape.setFillColor(sf::Color::White);
    m_label_background_shape.setPosition(m_label_shape.getPosition() - offset);
    m_label_background_shape.setSize({m_label_shape.getGlobalBounds().width + offset.x * 2, m_label_shape.getGlobalBounds().height + offset.y * 2});
}

void ConnectorShape::draw(Window *window) {
    window->draw(m_shape);

    if (!m_label.empty()) {
        window->draw(m_label_background_shape);
        window->draw(m_label_shape);
    }
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
