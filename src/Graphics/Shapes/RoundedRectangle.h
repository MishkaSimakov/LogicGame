#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <SFML/Graphics.hpp>
#include <cmath>

class RoundedRectangle : public sf::Shape {
public:
    enum corners {
        TOP_LEFT = 1 << 0,
        TOP_RIGHT = 1 << 1,
        BOTTOM_RIGHT = 1 << 2,
        BOTTOM_LEFT = 1 << 3,
        ALL = 15
    };

    RoundedRectangle(
            const sf::Vector2f &position,
            const sf::Vector2f &size,
            float radius = 10.f,
            unsigned char corners_to_round = corners::ALL,
            int points = 10
    );

    size_t getPointCount() const override {
        return m_vertices.size();
    }

    sf::Vector2f getPoint(std::size_t index) const override {
        return m_vertices[index];
    }

protected:
    std::vector<sf::Vector2f> m_vertices;
};

#endif // ROUNDEDRECTANGLE_H
