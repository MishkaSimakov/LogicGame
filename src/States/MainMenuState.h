#ifndef LOGICGAMEENGINE_MAINMENUSTATE_H
#define LOGICGAMEENGINE_MAINMENUSTATE_H

#include "BaseState.h"
#include "SFML/Graphics.hpp"

class MainMenuState : public BaseState {
public:
    explicit MainMenuState(StateManager *stateManager) :
            BaseState(stateManager) {}

    void onCreate() override;
    void onDestroy() override;
    void activate() override;
    void deactivate() override;
    void update(const sf::Time &time) override;
    void draw() override;

protected:
};


#endif //LOGICGAMEENGINE_MAINMENUSTATE_H
