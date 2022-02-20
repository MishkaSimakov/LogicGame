#ifndef LOGICGAMEENGINE_WRAPPINGTEXT_H
#define LOGICGAMEENGINE_WRAPPINGTEXT_H

#include "ResourceHolder.h"
#include <string>
#include <SFML/Graphics.hpp>

class WrappingText : public sf::Drawable {
public:
    WrappingText(
            sf::Vector2f position, float max_width, std::wstring content,
            int font_size = 20, const std::string &font_name = "arial", sf::Uint32 style = sf::Text::Regular
    );

    void setPosition(const sf::Vector2f &position);

    void setString(const std::wstring &string);

    sf::FloatRect getGlobalBounds() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void parseContent();

    sf::Vector2f m_position;

    sf::Text m_text;

    std::wstring m_content;
    int m_font_size;
    float m_max_width;
};


#endif //LOGICGAMEENGINE_WRAPPINGTEXT_H
