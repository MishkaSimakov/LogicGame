#include "WireShape.h"


void WireShape::update() {
    if (m_start_connector) m_start = m_start_connector->getPosition();
    if (m_end_connector) m_end = m_end_connector->getPosition();

    bool is_active = m_start_connector != nullptr && m_start_connector->getValue();

    sf::Color wire_color = is_active
                           ? sf::Color(182, 37, 25)
                           : sf::Color(158, 158, 158);
    sf::Color outline_color(220, 220, 220);

    auto &last_point = m_start;

    m_segments.clear();
    m_outline_segments.clear();

    for (auto &waypoint: m_waypoints) {
        // updating corners position
        appendSegment(last_point, waypoint, m_width, &m_segments, wire_color);
        appendSegment(last_point, waypoint, m_outline_width + m_width, &m_outline_segments, outline_color);

        last_point = waypoint;
    }

    appendSegment(last_point, m_end, m_width, &m_segments, wire_color);
    appendSegment(last_point, m_end, m_width + m_outline_width, &m_outline_segments, outline_color);
}

void WireShape::draw(Window *window) {
    if (m_is_selected) window->draw(m_outline_segments);
    window->draw(m_segments);
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

bool WireShape::checkClick(const sf::Vector2f &position) {
    for (int i = 0; i < m_outline_segments.getVertexCount() - 2; ++i) {
        if (isPointInTriangle(
                position,
                m_outline_segments[i].position,
                m_outline_segments[i + 1].position,
                m_outline_segments[i + 2].position
        ))
            return true;
    }

    return false;
}

void WireShape::appendSegment(sf::Vector2f start, sf::Vector2f end, float width, sf::VertexArray *vertex_array,
                              sf::Color color) {
    double rot = std::atan2f(end.x - start.x, end.y - start.y);
    float X1, Y1, X2, Y2;
    X1 = (float) sin(rot + M_PI_2) * (width / 2); // + 90°
    Y1 = (float) cos(rot + M_PI_2) * (width / 2); // + 90°
    X2 = (float) sin(rot + M_PI_2 * 3) * (width / 2); // + 270°
    Y2 = (float) cos(rot + M_PI_2 * 3) * (width / 2); // + 270°

    vertex_array->append(sf::Vertex(start + sf::Vector2f(X1, Y1), color));
    vertex_array->append(sf::Vertex(start + sf::Vector2f(X2, Y2), color));
    vertex_array->append(sf::Vertex(end + sf::Vector2f(X1, Y1), color));
    vertex_array->append(sf::Vertex(end + sf::Vector2f(X2, Y2), color));
}

float WireShape::sign(
        const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c
) {
    return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

bool WireShape::isPointInTriangle(
        const sf::Vector2f &point,
        const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c
) {
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(point, a, b);
    d2 = sign(point, b, c);
    d3 = sign(point, c, a);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

size_t WireShape::getSegmentIdByPosition(const sf::Vector2f &position) {
    return 0;
}

size_t WireShape::addWaypoint(const sf::Vector2f &position, size_t segment_id) {
    return 0;
}

void WireShape::dragWaypoint(size_t waypoint_id, const sf::Vector2f &position) {

}

bool WireShape::needToRemoveWaypoint(size_t waypoint_id) {
    sf::Vector2f prev_waypoint_pos;
    sf::Vector2f next_waypoint_pos;
    sf::Vector2f waypoint_pos = m_waypoints[waypoint_id];

    if (waypoint_id == 0)
        prev_waypoint_pos = m_start_connector->getPosition();
    else
        prev_waypoint_pos = m_waypoints[waypoint_id - 1];

    if (waypoint_id == m_waypoints.size() - 1)
        next_waypoint_pos = m_end_connector->getPosition();
    else
        next_waypoint_pos = m_waypoints[waypoint_id + 1];

    if (abs((waypoint_pos.x - prev_waypoint_pos.x) / (waypoint_pos.y - prev_waypoint_pos.y) - (next_waypoint_pos.x - waypoint_pos.x) / (next_waypoint_pos.y - waypoint_pos.x))) {

    }
}

void WireShape::removeWaypoint(size_t waypoint_id) {
    m_waypoints.erase(m_waypoints.begin() + (long) waypoint_id);
}
