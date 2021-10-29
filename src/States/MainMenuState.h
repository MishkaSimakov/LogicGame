#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "BaseState.h"
#include "RelativeButton.h"
#include "Game.h"

class MainMenuState : public BaseState
{
public:
    MainMenuState(Game &game);

    virtual void handleInput() {}

    virtual void handleEvent(sf::Event);

    virtual void update(sf::Time delta);

    virtual void render(sf::RenderTarget &renderer);
private:
    gui::RelativeButton m_play_button;
};

#endif // MAINMENUSTATE_H
