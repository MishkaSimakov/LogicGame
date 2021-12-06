#ifndef LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
#define LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H

#include "StaticLogicalComponent.h"
#include "Widget.h"
#include "RoundedRectangle.h"
#include "Colors.h"
#include <memory>

namespace gui {
    class StaticComponentsBlock : public Widget {
    public:
        StaticComponentsBlock();

        virtual bool handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

    private:
        RoundedRectangle m_background;
        std::vector<std::unique_ptr<gui::StaticLogicalComponent>> m_static_logical_components;
    };
}


#endif //LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
