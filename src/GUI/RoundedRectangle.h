#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include "Widget.h"
#include "SFML/Graphics.hpp"
#include <cmath>

namespace gui {
    class RoundedRectangle : public Widget {
    public:
        const static unsigned char TOP_LEFT = 1;
        const static unsigned char TOP_RIGHT = 2;
        const static unsigned char BOTTOM_RIGHT = 4;
        const static unsigned char BOTTOM_LEFT = 8;
        const static unsigned char ALL = 15;

        RoundedRectangle(
                const sf::Vector2f &position,
                const sf::Vector2f &rect_size,
                float radius,
                const sf::Color &color,
                unsigned char corners_to_round = ALL,
                float outline = 0.f,
                const sf::Color &outline_color = sf::Color::Black,
                int points = 10
        );

        virtual void render(sf::RenderTarget &renderer);

    protected:
        void generateShape();

        sf::Vector2f m_position;
        sf::Vector2f m_size;
        float m_radius;
        sf::Color m_color;
        unsigned char m_corners_to_round;
        float m_outline;
        sf::Color m_outline_color;
        int m_points;

        sf::ConvexShape m_shape;
    };
}

#endif // ROUNDEDRECTANGLE_H
