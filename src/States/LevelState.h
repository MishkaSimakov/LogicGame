#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "DocumentationBlock.h"
#include "Simulation.h"
#include "BaseState.h"
#include "ResourceHolder.h"
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
    gui::Simulation m_simulation;

    std::vector<gui::ActingLogicalComponent> m_acting_logical_components;
    std::vector<gui::StaticLogicalComponent> m_static_logical_components;
};

#endif // LEVELSTATE_H
