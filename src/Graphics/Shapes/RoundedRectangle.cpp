#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle(
        const sf::Vector2f &size,
        float radius,
        unsigned char corners_to_round,
        int points
) : m_size(size), m_radius(radius), m_corners_to_round(corners_to_round), m_points(points) {
    generatePoints();
    update();
}

void RoundedRectangle::setSize(const sf::Vector2f &size) {
    m_size = size;

    generatePoints();
    update();
}

void RoundedRectangle::generatePoints() {
    int points_count = (m_corners_to_round & TOP_LEFT ? m_points : 1) +
                       (m_corners_to_round & TOP_RIGHT ? m_points : 1) +
                       (m_corners_to_round & BOTTOM_RIGHT ? m_points : 1) +
                       (m_corners_to_round & BOTTOM_LEFT ? m_points : 1);

    m_vertices.clear();
    m_vertices.reserve(points_count);

    float x = 0, y;
    int i;

    if (m_corners_to_round & TOP_RIGHT) {
        for (i = 0; i < m_points; ++i) {
            x += m_radius / (float) m_points;
            y = std::sqrt(m_radius * m_radius - x * x);
            m_vertices.emplace_back(x + m_size.x - m_radius, -y + m_radius);
        }
    } else {
        m_vertices.emplace_back(m_size.x, 0);
    }

    if (m_corners_to_round & BOTTOM_RIGHT) {
        y = 0;
        for (i = 0; i < m_points; ++i) {
            y += m_radius / (float) m_points;
            x = std::sqrt(m_radius * m_radius - y * y);
            m_vertices.emplace_back(m_size.x + x - m_radius, m_size.y - m_radius + y);
        }
    } else {
        m_vertices.emplace_back(m_size.x, m_size.y);
    }

    if (m_corners_to_round & BOTTOM_LEFT) {
        x = 0;
        for (i = 0; i < m_points; ++i) {
            x += m_radius / (float) m_points;
            y = std::sqrt(m_radius * m_radius - x * x);
            m_vertices.emplace_back(m_radius - x, m_size.y - m_radius + y);
        }
    } else {
        m_vertices.emplace_back(0, m_size.y);
    }

    if (m_corners_to_round & TOP_LEFT) {
        y = 0;
        for (i = 0; i < m_points; ++i) {
            y += m_radius / (float) m_points;
            x = std::sqrt(m_radius * m_radius - y * y);
            m_vertices.emplace_back(-x + m_radius, m_radius - y);
        }
    } else {
        m_vertices.emplace_back(0, 0);
    }
}
