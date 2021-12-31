#ifndef LOGICGAMEENGINE_OR_H
#define LOGICGAMEENGINE_OR_H

#include "BaseLogicalComponent.h"

class Or : public BaseLogicalComponent {
public:
    Or() : BaseLogicalComponent(L"ИЛИ", "LogicalComponents/or", 2, 5) {}

    void processInput(const std::vector<bool> *input, std::vector<bool> *output) const override {
        assert(getInputsCount() == input->size());
        assert(getOutputsCount() == input->size());

        output->at(0) = input->at(0) && input->at(1);
    }
};

#endif //LOGICGAMEENGINE_OR_H
