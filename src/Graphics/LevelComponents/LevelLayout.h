#ifndef LOGICGAMEENGINE_LEVELLAYOUT_H
#define LOGICGAMEENGINE_LEVELLAYOUT_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class RectangleLayout : public sf::FloatRect {
public:
    // constructors inheritance
    using sf::FloatRect::FloatRect;

    sf::Vector2f getSize() const {
        return {width, height};
    }

    sf::Vector2f getPosition() const {
        return {left, top};
    }
};

class TextLayout : public sf::FloatRect {
public:
    enum class Orientation {
        LEFT,
        RIGHT,
        CENTER
    };

    // width is available space for string (used for position calculation when orientation is RIGHT or CENTER)
    TextLayout(const sf::Vector2f &position, float width, int font_size, Orientation orientation = Orientation::LEFT) :
            sf::FloatRect(position, {width, (float) font_size}),
            m_font_size(font_size),
            m_orientation(orientation) {};

    [[nodiscard]] sf::Vector2f getSize() const {
        return {width, height};
    }

    [[nodiscard]] sf::Vector2f getPosition(float string_width) const {
        float offset = 0;

        if (m_orientation == Orientation::RIGHT) offset = width - string_width;
        else if (m_orientation == Orientation::CENTER) offset = (width - string_width) / 2;

        return {left + offset, top};
    }

    [[nodiscard]] sf::Vector2f getPosition() const {
        assert(m_orientation == Orientation::LEFT);

        return {left, top};
    }

    [[nodiscard]] int getFontSize() const {
        return m_font_size;
    }

protected:
    int m_font_size;
    Orientation m_orientation;
};

// structure to store layout of level state
struct LevelLayout {
    explicit LevelLayout(const sf::Vector2f &window_size) :
            offset(25., 25.),
            border_radius(18),
            documentation_block({0., 0.}, {800., window_size.y}),
            documentation_block_title(offset, documentation_block.width - 2 * offset.x, 40,
                                      TextLayout::Orientation::CENTER),
            documentation_block_description(
                    {offset.x, documentation_block_title.top + documentation_block_title.height + offset.y},
                    documentation_block.width - 2 * offset.x, 30
            ) {}

    // names without "m_" prefix for easier access from another classes
    const sf::Vector2f offset;

    const float border_radius;

    const RectangleLayout documentation_block;
    const TextLayout documentation_block_title;
    const TextLayout documentation_block_description;
};


#endif //LOGICGAMEENGINE_LEVELLAYOUT_H
