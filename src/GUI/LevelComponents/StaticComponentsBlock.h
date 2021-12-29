#ifndef LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
#define LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H

#include "Widget.h"
#include "StaticLogicalComponent.h"
#include "RoundedRectangle.h"
#include "Colors.h"
#include "And.h"
#include "Or.h"
#include <memory>

namespace gui {
    class StaticComponentsBlock : public Widget {
    public:
        StaticComponentsBlock();

        bool handleEvent(Event e) override;

        void render(sf::RenderTarget &renderer) override;

        void addStaticComponent(BaseLogicalComponent &&logical_component_data);
    private:
        sf::Vector2f m_right_position;

        RoundedRectangle m_background;
        std::vector<std::unique_ptr<StaticLogicalComponent>> m_static_logical_components;
    };
}


#endif //LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
