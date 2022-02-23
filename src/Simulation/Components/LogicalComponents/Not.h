#ifndef LOGICGAMEENGINE_NOT_H
#define LOGICGAMEENGINE_NOT_H

#include "BaseLogicalComponent.h"

class Not : public BaseLogicalComponent {
public:
    Not() : BaseLogicalComponent(L"НЕ", 1, 1) {}

    void processInput(const std::vector<bool> *input, std::vector<bool> *output) const override {
        assert(getInputsCount() == input->size());

        output->insert(output->begin(), !input->at(0));
    }
};

#endif //LOGICGAMEENGINE_NOT_H
