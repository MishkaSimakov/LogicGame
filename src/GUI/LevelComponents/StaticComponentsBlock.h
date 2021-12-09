#ifndef LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
#define LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H

#include "Widget.h"
#include "StaticLogicalComponent.h"
#include "RoundedRectangle.h"
#include "Colors.h"
#include "And.h"
#include <memory>

namespace gui {
    class StaticComponentsBlock : public Widget {
    public:
        StaticComponentsBlock();

        virtual bool handleEvent(Event e);

        virtual void render(sf::RenderTarget &renderer);

    private:
        RoundedRectangle m_background;
        std::vector<std::unique_ptr<gui::StaticLogicalComponent>> m_static_logical_components;
    };
}


#endif //LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
