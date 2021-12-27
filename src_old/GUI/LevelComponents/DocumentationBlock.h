#ifndef LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
#define LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H

#include <string>
#include "Widget.h"
#include "RoundedRectangle.h"
#include "Colors.h"
#include "WrappingText.h"
#include "Button.h"

namespace gui {
    class DocumentationBlock : public Widget {
    public:
        DocumentationBlock(const std::wstring &title, const std::wstring &description, float height);

        bool handleEvent(Event e) override;

        virtual void render(sf::RenderTarget &renderer);
    private:
        RoundedRectangle m_background;
        WrappingText m_title;
        WrappingText m_description;

        Button m_hide_button;
        Button m_show_button;

        bool m_is_opened = true;
    };
}


#endif //LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
