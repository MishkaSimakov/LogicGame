#include "WireShape.h"

void WireShape::update() {
    if (m_start_connector) m_start = m_start_connector->getPosition();
    if (m_end_connector) m_end = m_end_connector->getPosition();

    // updating corners position
    float width = 3;
    float rot = std::atan2f(m_end.x - m_start.x, m_end.y - m_start.y);
    float X1, Y1, X2, Y2;
    X1 = sinf(rot + M_PI_2) * (width / 2); // + 90°
    Y1 = cosf(rot + M_PI_2) * (width / 2); // + 90°
    X2 = sinf(rot + M_PI_2 * 3) * (width / 2); // + 270°
    Y2 = cosf(rot + M_PI_2 * 3) * (width / 2); // + 270°

    m_shape[0].position = m_start + sf::Vector2f(X1, Y1);
    m_shape[1].position = m_start + sf::Vector2f(X2, Y2);
    m_shape[2].position = m_end + sf::Vector2f(X2, Y2);
    m_shape[3].position = m_end + sf::Vector2f(X1, Y1);

    for (int i = 0; i < m_shape.getVertexCount(); ++i) {
        m_shape[i].color = sf::Color::Black;
    }
}

void WireShape::draw(Window *window) {
    window->draw(m_shape);
}

void WireShape::dragTo(const sf::Vector2f &position) {
    if (!m_start_connector) m_start = position;
    else if (!m_end_connector) m_end = position;

    update();
}

ConnectorShape *WireShape::getDragOriginConnector() {
    return m_start_connector ? m_start_connector : m_end_connector;
}

void WireShape::addMissingConnector(ConnectorShape *connector) {
    if (!m_start_connector) m_start_connector = connector;
    else if (!m_end_connector) m_end_connector = connector;
}
