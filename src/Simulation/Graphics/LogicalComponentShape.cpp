#include "LogicalComponentShape.h"

void LogicalComponentShape::draw(Window *window) {
    window->draw(m_shape);
}

void LogicalComponentShape::update() {
    m_shape.setSize(m_size);
    m_shape.setPosition(m_position);
    m_shape.setTexture(m_texture);
}

sf::Vector2f LogicalComponentShape::getConnectorPosition(
        ConnectorPlacement placement,
        int connectors_count,
        int connector_no
) {
    if (placement == ConnectorPlacement::TOP) {
        return m_position + sf::Vector2f(m_size.x / (float) (connectors_count + 1) * (float) (connector_no + 1), .0f);
    } else if (placement == ConnectorPlacement::BOTTOM) {
        return m_position +
               sf::Vector2f(m_size.x / (float) (connectors_count + 1) * (float) (connector_no + 1), m_size.y);
    }

    // TODO: add other types of placement
    return m_position;
}

bool LogicalComponentShape::checkClick(const sf::Vector2f &position) {
    return m_shape.getGlobalBounds().contains( position);
}