#ifndef LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
#define LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H


#include "ResourceHolder.h"
#include "WrappingText.h"
#include "RoundedRectangle.h"
#include "SharedContext.h"
#include "Window.h"

#include <string>

class DocumentationBlock {
public:
    DocumentationBlock(const std::wstring &title, const std::wstring &description, const sf::Vector2f &size,
                       SharedContext *sharedContext);

    void draw();

private:
    sf::Vector2f m_offset{25.f, 25.f};

    RoundedRectangle m_background;
    WrappingText m_title;
    WrappingText m_description;

    SharedContext *m_shared_context;

    bool m_is_opened{true};
};


#endif //LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
