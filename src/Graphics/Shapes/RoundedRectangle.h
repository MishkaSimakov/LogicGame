#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class RoundedRectangle : public sf::Shape {
public:
    enum Corners {
        TOP_LEFT = 1 << 0,
        TOP_RIGHT = 1 << 1,
        BOTTOM_RIGHT = 1 << 2,
        BOTTOM_LEFT = 1 << 3,
        ALL = 15
    };

    explicit RoundedRectangle(
            const sf::Vector2f &size = {0, 0},
            float radius = 10.f,
            unsigned char corners_to_round = Corners::ALL,
            int points = 10
    );

    void setSize(const sf::Vector2f& size);

    size_t getPointCount() const override {
        return m_vertices.size();
    }

    sf::Vector2f getPoint(std::size_t index) const override {
        return m_vertices[index];
    }

protected:
    void generatePoints();

    sf::Vector2f m_size;
    float m_radius;
    unsigned char m_corners_to_round;
    int m_points;


    std::vector<sf::Vector2f> m_vertices;
};

#endif // ROUNDEDRECTANGLE_H
