#ifndef BASESTATE_H
#define BASESTATE_H

#include "SFML/Graphics.hpp"
#include "Event.h"
#include <iostream>

class Game;

class BaseState
{
public:
    BaseState(Game &game) : m_game(&game) {};

    virtual void handleEvent(Event) {}

    virtual void handleInput() = 0;

    virtual void update(sf::Time delta) {}

    virtual void fixedUpdate(sf::Time delta) {}

    virtual void render(sf::RenderTarget &renderer) = 0;
protected:
    Game *m_game;
};

#endif // BASESTATE_H
