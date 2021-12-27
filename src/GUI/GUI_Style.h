#ifndef LOGICGAMEENGINE_GUI_STYLE_H
#define LOGICGAMEENGINE_GUI_STYLE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>


enum class GUI_ElementState {
    Neutral, Focused, Clicked
};

struct GUI_Style {
    sf::Vector2f m_size; // Element size.
    // Background properties.
    sf::Color m_backgroundColor;
    sf::Color m_elementColor;
    std::string m_backgroundImage;
    sf::Color m_backgroundImageColor;
    // Text properties.
    sf::Color m_textColor;
    std::string m_textFont;
    sf::Vector2f m_textPadding;
    unsigned int m_textSize;
    bool m_textCenterOrigin;
    // Glyph properties.
    std::string m_glyph;
    sf::Vector2f m_glyphPadding;
};

struct GUI_Visual {
    sf::RectangleShape m_backgroundSolid;
    sf::Sprite m_backgroundImage;
    sf::Sprite m_glyph;
    sf::Text m_text;
};


#endif //LOGICGAMEENGINE_GUI_STYLE_H
