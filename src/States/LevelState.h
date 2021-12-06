#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "DocumentationBlock.h"
#include "Simulation.h"
#include <memory>
#include "StaticLogicalComponent.h"
#include "StaticComponentsBlock.h"
#include "BaseState.h"
#include "Game.h"


class LevelState : public BaseState
{
public:
    LevelState(Game &game);

    virtual void handleInput() {}

    virtual void handleEvent(sf::Event);

    virtual void update(sf::Time delta);

    virtual void render(sf::RenderTarget &renderer);
private:
    gui::DocumentationBlock m_documentation_block;
    gui::StaticComponentsBlock m_static_components_block;
};

#endif // LEVELSTATE_H
