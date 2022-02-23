#ifndef LOGICGAMEENGINE_DOCUMENTATION_H
#define LOGICGAMEENGINE_DOCUMENTATION_H

#include "Level.h"
#include "WrappingText.h"
#include "TruthTable.h"
#include "LevelLayout.h"

#include <SFML/Graphics/Drawable.hpp>
#include <string>


class Documentation : public sf::Drawable {
public:
    Documentation(float max_width, const Level &level, const TextLayout &description_layout);

    void setLevel(const Level &level);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::FloatRect getGlobalBounds() const;

    void setPosition(const sf::Vector2f &position);

protected:
    void update();

    sf::Vector2f m_position;
    float m_max_width;
    float m_offset{50.f};

    WrappingText m_description;

    TruthTable m_truth_table;
};


#endif //LOGICGAMEENGINE_DOCUMENTATION_H
