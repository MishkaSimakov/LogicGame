#ifndef LOGICGAMEENGINE_WRAPPINGTEXT_H
#define LOGICGAMEENGINE_WRAPPINGTEXT_H

#include <string>
#include "Widget.h"
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Colors.h"

namespace gui {
    class WrappingText : public Widget {
    public:
        WrappingText(
                sf::Vector2f position, float max_width, std::string content,
                int font_size = 20, const std::string &font_name = "arial"
        );

        virtual void render(sf::RenderTarget &renderer);

    protected:
        void parseContent();

        sf::Text m_text;

        std::string m_content;
        int m_font_size;
        float m_max_width;
    };
}


#endif //LOGICGAMEENGINE_WRAPPINGTEXT_H
