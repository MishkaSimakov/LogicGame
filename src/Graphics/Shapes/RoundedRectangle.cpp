#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle(
        const sf::Vector2f &size,
        float radius,
        unsigned char corners_to_round,
        int points
) {
    int points_count = (corners_to_round & TOP_LEFT ? points : 1) +
                       (corners_to_round & TOP_RIGHT ? points : 1) +
                       (corners_to_round & BOTTOM_RIGHT ? points : 1) +
                       (corners_to_round & BOTTOM_LEFT ? points : 1);

    m_vertices.reserve(points_count);

    float x = 0, y;
    int i;

    if (corners_to_round & TOP_RIGHT) {
        for (i = 0; i < points; ++i) {
            x += radius / (float) points;
            y = std::sqrt(radius * radius - x * x);
            m_vertices.emplace_back(x + size.x - radius, -y + radius);
        }
    } else {
        m_vertices.emplace_back(size.x, 0);
    }

    if (corners_to_round & BOTTOM_RIGHT) {
        y = 0;
        for (i = 0; i < points; ++i) {
            y += radius / (float) points;
            x = std::sqrt(radius * radius - y * y);
            m_vertices.emplace_back(size.x + x - radius, size.y - radius + y);
        }
    } else {
        m_vertices.emplace_back(size.x, size.y);
    }

    if (corners_to_round & BOTTOM_LEFT) {
        x = 0;
        for (i = 0; i < points; ++i) {
            x += radius / (float) points;
            y = std::sqrt(radius * radius - x * x);
            m_vertices.emplace_back(radius - x, size.y - radius + y);
        }
    } else {
        m_vertices.emplace_back(0, size.y);
    }

    if (corners_to_round & TOP_LEFT) {
        y = 0;
        for (i = 0; i < points; ++i) {
            y += radius / (float) points;
            x = std::sqrt(radius * radius - y * y);
            m_vertices.emplace_back(-x + radius, radius - y);
        }
    } else {
        m_vertices.emplace_back(0, 0);
    }

    update();
}
