#ifndef LOGICGAMEENGINE_LEVELCONTROLS_H
#define LOGICGAMEENGINE_LEVELCONTROLS_H

#include "SharedContext.h"

#include <TGUI/TGUI.hpp>

class LevelControls {
public:
    LevelControls(SharedContext *sharedContext);

protected:
    SharedContext *m_shared_context;
};


#endif //LOGICGAMEENGINE_LEVELCONTROLS_H
