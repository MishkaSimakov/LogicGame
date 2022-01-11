#ifndef LOGICGAMEENGINE_LEVELCONTROLS_H
#define LOGICGAMEENGINE_LEVELCONTROLS_H

#include "SharedContext.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <functional>

class LevelState;

class LevelControls {
public:
    LevelControls(SharedContext *sharedContext, void(LevelState::*run_tests_cb)(), LevelState *object);

    void draw();

protected:
    SharedContext *m_shared_context;

    sf::Vector2f m_run_tests_btn_size{50, 50};
    Button m_run_tests_btn;

    std::function<void(const sf::Event &event)> m_run_tests_cb;
};


#endif //LOGICGAMEENGINE_LEVELCONTROLS_H
