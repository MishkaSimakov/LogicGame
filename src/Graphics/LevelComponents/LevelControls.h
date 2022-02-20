#ifndef LOGICGAMEENGINE_LEVELCONTROLS_H
#define LOGICGAMEENGINE_LEVELCONTROLS_H

#include "SharedContext.h"
#include "Button.h"

#include <SFML/Graphics.hpp>

class LevelState;

class LevelControls {
public:
    LevelControls(SharedContext *sharedContext, void(LevelState::*run_tests_cb)(), void(LevelState::*quit_level_cb)(),
                  LevelState *object);

    void draw();

protected:
    SharedContext *m_shared_context;

    sf::Vector2f m_run_tests_btn_size{40, 40};
    Button m_run_tests_btn;

    sf::Vector2f m_quit_level_btn_size{40, 40};
    Button m_quit_level_btn;
};


#endif //LOGICGAMEENGINE_LEVELCONTROLS_H
