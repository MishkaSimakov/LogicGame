#ifndef LOGICGAMEENGINE_SHAREDCONTEXT_H
#define LOGICGAMEENGINE_SHAREDCONTEXT_H

#include "Window.h"
#include "EventManager.h"

struct SharedContext {
    SharedContext() : m_wind(nullptr), m_eventManager(nullptr) {}

    Window *m_wind;
    EventManager *m_eventManager;
};

#endif //LOGICGAMEENGINE_SHAREDCONTEXT_H
