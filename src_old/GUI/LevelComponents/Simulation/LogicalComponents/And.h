#ifndef LOGICGAMEENGINE_AND_H
#define LOGICGAMEENGINE_AND_H

#include "BaseLogicalComponent.h"

class And : public BaseLogicalComponent {
public:
    And() : BaseLogicalComponent(L"И", "LogicalComponents/and", 2, 2) {}
};

#endif //LOGICGAMEENGINE_AND_H
