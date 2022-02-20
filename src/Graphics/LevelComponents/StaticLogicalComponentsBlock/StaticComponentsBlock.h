#ifndef LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
#define LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H

#include "Window.h"
#include "SharedContext.h"
#include "BaseLogicalComponent.h"
#include "StaticLogicalComponent.h"
#include "RoundedRectangle.h"

#include <SFML/Graphics.hpp>
#include <vector>

class StaticComponentsBlock {
public:
    StaticComponentsBlock(
            const sf::Vector2f &position,
            const sf::Vector2f &size,
            SharedContext *sharedContext
    );

    void draw();

    void clearStaticComponents();

    void addStaticComponent(const BaseLogicalComponent *logical_component_data);

    std::optional<std::pair<const BaseLogicalComponent *, const sf::Vector2f &>>
    getClickedComponentData(const sf::Vector2f &position);

    inline sf::Vector2f getNextComponentPosition();

    inline sf::Vector2f getComponentPosition(int n);

    void setPosition(const sf::Vector2f &position);

    void setSize(const sf::Vector2f &size);

    const sf::Vector2f &getSize() const;

private:
    void update();

    sf::Vector2f m_position;
    sf::Vector2f m_size;

    RoundedRectangle m_background;
    std::vector<std::unique_ptr<StaticLogicalComponent>> m_components;

    sf::Vector2f m_offset{10.f, 10.f};
    float m_space_between{10.f};

    SharedContext *m_shared_context;
};


#endif //LOGICGAMEENGINE_STATICCOMPONENTSBLOCK_H
