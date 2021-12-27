#ifndef LOGICGAMEENGINE_MAINMENUSTATE_H
#define LOGICGAMEENGINE_MAINMENUSTATE_H

#include "BaseState.h"
#include "TGUI/TGUI.hpp"

class MainMenuState : public BaseState {
public:
    explicit MainMenuState(StateManager *stateManager) :
            BaseState(stateManager),
            m_play_button(tgui::Button::create()) {}

    void onCreate() override;
    void onDestroy() override;
    void activate() override;
    void deactivate() override;
    void update(const sf::Time &time) override;
    void draw() override;

protected:
    tgui::Button::Ptr m_play_button;
};


#endif //LOGICGAMEENGINE_MAINMENUSTATE_H
