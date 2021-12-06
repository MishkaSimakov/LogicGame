#ifndef LOGICGAMEENGINE_WRAPPINGTEXT_H
#define LOGICGAMEENGINE_WRAPPINGTEXT_H

#include "Widget.h"
#include <string>
#include "ResourceHolder.h"
#include "Colors.h"

namespace gui {
    class WrappingText : public Widget {
    public:
        WrappingText(
                sf::Vector2f position, float max_width, std::wstring content,
                int font_size = 20, const std::string &font_name = "arial"
        );

        virtual void render(sf::RenderTarget &renderer);

    protected:
        void parseContent();

        sf::Text m_text;

        std::wstring m_content;
        int m_font_size;
        float m_max_width;
    };
}


#endif //LOGICGAMEENGINE_WRAPPINGTEXT_H
