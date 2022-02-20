#ifndef LOGICGAMEENGINE_AND_H
#define LOGICGAMEENGINE_AND_H

#include "BaseLogicalComponent.h"

class And : public BaseLogicalComponent {
public:
    And() : BaseLogicalComponent(L"И", "LogicalComponents/and", 2, 1) {}

    void processInput(const std::vector<bool> *input, std::vector<bool> *output) const override {
        assert(getInputsCount() == input->size());

        output->insert(output->begin(), input->at(0) && input->at(1));
    }
};

#endif //LOGICGAMEENGINE_AND_H
