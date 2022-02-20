#ifndef LOGICGAMEENGINE_SHAREDCONTEXT_H
#define LOGICGAMEENGINE_SHAREDCONTEXT_H

class Window;
class EventManager;
class LevelManager;

struct SharedContext {
    SharedContext() : m_wind(nullptr), m_eventManager(nullptr), m_level_manager(nullptr) {}

    Window *m_wind;
    EventManager *m_eventManager;
    LevelManager *m_level_manager;
};

#endif //LOGICGAMEENGINE_SHAREDCONTEXT_H
