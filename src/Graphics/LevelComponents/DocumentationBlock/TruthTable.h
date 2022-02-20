#ifndef LOGICGAMEENGINE_TRUTHTABLE_H
#define LOGICGAMEENGINE_TRUTHTABLE_H


#include "Level.h"
#include "ResourceHolder.h"

#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>

class TruthTable : public sf::Drawable {
public:
    TruthTable(const sf::Vector2f &position, const Level &level);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setPosition(const sf::Vector2f &position);

    [[nodiscard]] sf::FloatRect getGlobalBounds() const {
        return {m_position, {500, 100}};
    }

    void setLevel(const Level &level);

protected:
    sf::Vector2f m_position;

    sf::Text m_title;

    sf::VertexArray m_borders;
    std::vector<sf::Text> m_cells;
};


#endif //LOGICGAMEENGINE_TRUTHTABLE_H
