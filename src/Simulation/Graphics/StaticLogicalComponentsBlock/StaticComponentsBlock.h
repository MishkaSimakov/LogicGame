#ifndef LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
#define LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H

#include "Window.h"
#include "SharedContext.h"
#include "BaseLogicalComponent.h"
#include "StaticLogicalComponent.h"
#include "RoundedRectangle.h"

#include <SFML/Graphics.hpp>

class StaticComponentsBlock {
public:
    StaticComponentsBlock(
            const sf::Vector2f &position,
            const sf::Vector2f &size,
            SharedContext *sharedContext
    );

    void draw();

    void addStaticComponent(BaseLogicalComponent &&logical_component_data);

    std::optional<std::pair<BaseLogicalComponent, sf::Vector2f>> getClickedComponentData(const sf::Vector2f &position);

    inline sf::Vector2f nextComponentPosition();

private:
    sf::Vector2f m_position;
    sf::Vector2f m_size;

    RoundedRectangle m_background;
    std::vector<std::unique_ptr<StaticLogicalComponent>> m_components;

    sf::Vector2f m_offset{10.f, 10.f};
    float m_space_between{10.f};

    SharedContext *m_shared_context;
};


#endif //LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
