#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <BaseState.h>
#include "ResourceHolder.h"

class TestState : public BaseState
{
public:
    TestState(Game &game);

    virtual void handleInput() {}

    virtual void update(sf::Time delta);

    virtual void render(sf::RenderTarget &renderer);
private:
    sf::Text title;
};

#endif // TESTSTATE_H
