#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include "Widget.h"
#include <cmath>

namespace gui {
    class RoundedRectangle : public Widget {
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
                const sf::Vector2f &rect_size,
                float radius,
                const sf::Color &color,
                unsigned char corners_to_round = corners::ALL,
                float outline_thickness = 0.f,
                const sf::Color &outline_color = sf::Color::Black,
                int points = 10
        );

        virtual void render(sf::RenderTarget &renderer);

    protected:
        sf::ConvexShape m_shape;
    };
}

#endif // ROUNDEDRECTANGLE_H
