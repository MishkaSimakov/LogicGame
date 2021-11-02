#ifndef LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
#define LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H

#include <string>
#include "Widget.h"
#include "RoundedRectangle.h"
#include "Colors.h"
#include "WrappingText.h"

namespace gui {
    class DocumentationBlock : public Widget {
    public:
        DocumentationBlock(const std::string &title, const std::string &description, float height);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);
    private:
        RoundedRectangle m_background;
        WrappingText m_title;
        sf::Text m_description;

        int m_width;
    };
}


#endif //LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
