#include "RoundedRectangle.h"

namespace gui {
    RoundedRectangle::RoundedRectangle(
            const sf::Vector2f &position,
            const sf::Vector2f &rect_size,
            float radius,
            const sf::Color &color,
            unsigned char corners_to_round,
            float outline_thickness,
            const sf::Color &outline_color,
            int points
    ) {
        m_shape.setFillColor(color);

        m_shape.setOutlineThickness(outline_thickness);
        m_shape.setOutlineColor(outline_color);

        int points_count = (corners_to_round & TOP_LEFT ? points : 1) +
                           (corners_to_round & TOP_RIGHT ? points : 1) +
                           (corners_to_round & BOTTOM_RIGHT ? points : 1) +
                           (corners_to_round & BOTTOM_LEFT ? points : 1);

        m_shape.setPointCount(points_count);

        float x = 0, y;
        int i, point_id = 0;

        if (corners_to_round & TOP_RIGHT) {
            for (i = 0; i < points; ++i) {
                x += radius / (float) points;
                y = std::sqrt(radius * radius - x * x);
                m_shape.setPoint(point_id,
                                 sf::Vector2f(x + position.x + rect_size.x - radius, position.y - y + radius));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(position.x + rect_size.x, position.y));
            ++point_id;
        }

        if (corners_to_round & BOTTOM_RIGHT) {
            y = 0;
            for (i = 0; i < points; ++i) {
                y += radius / (float) points;
                x = std::sqrt(radius * radius - y * y);
                m_shape.setPoint(point_id, sf::Vector2f(position.x + rect_size.x + x - radius,
                                                        position.y + rect_size.y - radius + y));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(position.x + rect_size.x, position.y + rect_size.y));
            ++point_id;
        }

        if (corners_to_round & BOTTOM_LEFT) {
            x = 0;
            for (i = 0; i < points; ++i) {
                x += radius / (float) points;
                y = std::sqrt(radius * radius - x * x);
                m_shape.setPoint(point_id,
                                 sf::Vector2f(position.x + radius - x, position.y + rect_size.y - radius + y));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(position.x, position.y + rect_size.y));
            ++point_id;
        }

        if (corners_to_round & TOP_LEFT) {
            y = 0;
            for (i = 0; i < points; ++i) {
                y += radius / (float) points;
                x = std::sqrt(radius * radius - y * y);
                m_shape.setPoint(point_id, sf::Vector2f(position.x - x + radius, position.y + radius - y));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(position.x, position.y));
            ++point_id;
        }
    }

    void RoundedRectangle::render(sf::RenderTarget &renderer) {
        renderer.draw(m_shape);
    }
}
