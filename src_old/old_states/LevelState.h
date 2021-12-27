#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GUI/LevelComponents/Simulation/Simulation.h"
#include "Event.h"
#include "DocumentationBlock.h"
#include "StaticComponentsBlock.h"
#include "BaseState.h"
#include "Game.h"

#include <memory>


class LevelState : public BaseState
{
public:
    LevelState(Game &game);

    virtual void handleInput() {}

    virtual void handleEvent(Event e);

    virtual void update(sf::Time delta);

    virtual void render(sf::RenderTarget &renderer);
private:
    gui::DocumentationBlock m_documentation_block;
    gui::StaticComponentsBlock m_static_components_block;
};

#endif // LEVELSTATE_H
