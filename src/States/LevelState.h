#ifndef LOGICGAMEENGINE_LEVELSTATE_H
#define LOGICGAMEENGINE_LEVELSTATE_H

#include "BaseState.h"
#include "SimulationManager.h"
#include "StaticComponentsBlock.h"
#include "And.h"

class LevelState : public BaseState {
public:
    explicit LevelState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    void handleMousePressed(const sf::Event &event);

    SimulationManager m_simulation_manager;
    StaticComponentsBlock m_components_block;
};


#endif //LOGICGAMEENGINE_LEVELSTATE_H
