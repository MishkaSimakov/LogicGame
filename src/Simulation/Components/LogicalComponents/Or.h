#ifndef LOGICGAMEENGINE_OR_H
#define LOGICGAMEENGINE_OR_H

#include "BaseLogicalComponent.h"

class Or : public BaseLogicalComponent {
public:
    Or() : BaseLogicalComponent(L"ИЛИ", 2, 1) {}

    void processInput(const std::vector<bool> *input, std::vector<bool> *output) const override {
        assert(getInputsCount() == input->size());

        output->insert(output->begin(), input->at(0) || input->at(1));
    }
};

#endif //LOGICGAMEENGINE_OR_H
