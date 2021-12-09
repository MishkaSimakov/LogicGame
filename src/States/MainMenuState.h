#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "BaseState.h"
#include "Event.h"
#include "Button.h"
#include "Game.h"
#include "LevelState.h"

class MainMenuState : public BaseState
{
public:
    MainMenuState(Game &game);

    virtual void handleInput() {}

    virtual void handleEvent(Event);

    virtual void update(sf::Time delta);

    virtual void render(sf::RenderTarget &renderer);
private:
    gui::Button m_play_button;
};

#endif // MAINMENUSTATE_H
