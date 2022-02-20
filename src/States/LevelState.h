#ifndef LOGICGAMEENGINE_LEVELSTATE_H
#define LOGICGAMEENGINE_LEVELSTATE_H

#include "BaseState.h"
#include "SimulationManager.h"
#include "StaticComponentsBlock.h"
#include "DocumentationBlock.h"
#include "LevelControls.h"
#include "LevelManager.h"

#include "And.h"
#include "Or.h"
#include "Not.h"
#include "ComponentsDataFactory.h"

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

    void runTests();

    void mainMenu();

    void reloadLevel();

    const LevelLayout m_layout;

    int m_loaded_level_id;

    const float m_documentation_block_width{800.f};

    SimulationManager m_simulation_manager;
    StaticComponentsBlock m_components_block;
    DocumentationBlock m_documentation_block;
    LevelControls m_level_controls;

    ComponentsDataFactory m_components_data;
};


#endif //LOGICGAMEENGINE_LEVELSTATE_H
