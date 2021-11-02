#include "RoundedRectangle.h"

namespace gui {
    RoundedRectangle::RoundedRectangle(
            const sf::Vector2f &position,
            const sf::Vector2f &rect_size,
            float radius,
            const sf::Color &color,
            unsigned char corners_to_round,
            float outline,
            const sf::Color &outline_color,
            int points
    ) :
            m_position(position),
            m_size(rect_size),
            m_radius(radius),
            m_color(color),
            m_corners_to_round(corners_to_round),
            m_outline(outline),
            m_outline_color(outline_color),
            m_points(points) {
        generateShape();
    }

    void RoundedRectangle::generateShape() {
        m_shape.setFillColor(m_color);

        m_shape.setOutlineThickness(m_outline);
        m_shape.setOutlineColor(m_outline_color);

        int points_count = (m_corners_to_round & TOP_LEFT ? m_points : 1) +
                           (m_corners_to_round & TOP_RIGHT ? m_points : 1) +
                           (m_corners_to_round & BOTTOM_RIGHT ? m_points : 1) +
                           (m_corners_to_round & BOTTOM_LEFT ? m_points : 1);

        m_shape.setPointCount(points_count);

        float x = 0, y = 0;
        int i, point_id = 0;

        if (m_corners_to_round & TOP_RIGHT) {
            for (i = 0; i < m_points; ++i) {
                x += m_radius / m_points;
                y = std::sqrt(m_radius * m_radius - x * x);
                m_shape.setPoint(point_id,
                                 sf::Vector2f(x + m_position.x + m_size.x - m_radius, m_position.y - y + m_radius));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(m_position.x + m_size.x, m_position.y));
            ++point_id;
        }

        if (m_corners_to_round & BOTTOM_RIGHT) {
            y = 0;
            for (i = 0; i < m_points; ++i) {
                y += m_radius / m_points;
                x = std::sqrt(m_radius * m_radius - y * y);
                m_shape.setPoint(point_id, sf::Vector2f(m_position.x + m_size.x + x - m_radius,
                                                        m_position.y + m_size.y - m_radius + y));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(m_position.x + m_size.x, m_position.y + m_size.y));
            ++point_id;
        }

        if (m_corners_to_round & BOTTOM_LEFT) {
            x = 0;
            for (i = 0; i < m_points; ++i) {
                x += m_radius / m_points;
                y = std::sqrt(m_radius * m_radius - x * x);
                m_shape.setPoint(point_id,
                                 sf::Vector2f(m_position.x + m_radius - x, m_position.y + m_size.y - m_radius + y));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(m_position.x, m_position.y + m_size.y));
            ++point_id;
        }

        if (m_corners_to_round & TOP_LEFT) {
            y = 0;
            for (i = 0; i < m_points; ++i) {
                y += m_radius / m_points;
                x = std::sqrt(m_radius * m_radius - y * y);
                m_shape.setPoint(point_id, sf::Vector2f(m_position.x - x + m_radius, m_position.y + m_radius - y));
                ++point_id;
            }
        } else {
            m_shape.setPoint(point_id, sf::Vector2f(m_position.x, m_position.y));
            ++point_id;
        }
    }

    void RoundedRectangle::render(sf::RenderTarget &renderer) {
        renderer.draw(m_shape);
    }
}
