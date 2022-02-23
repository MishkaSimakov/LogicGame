#ifndef LOGICGAMEENGINE_XOR_H
#define LOGICGAMEENGINE_XOR_H

#include "BaseLogicalComponent.h"

class Xor : public BaseLogicalComponent {
public:
    Xor() : BaseLogicalComponent(L"XOR", 2, 1) {}

    void processInput(const std::vector<bool> *input, std::vector<bool> *output) const override {
        assert(getInputsCount() == input->size());

        output->insert(output->begin(), input->at(0) != input->at(1));
    }
};

#endif //LOGICGAMEENGINE_XOR_H
