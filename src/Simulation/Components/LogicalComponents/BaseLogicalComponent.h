#ifndef LOGICGAMEENGINE_BASELOGICALCOMPONENT_H
#define LOGICGAMEENGINE_BASELOGICALCOMPONENT_H

#include <string>
#include <utility>
#include <vector>
#include <SFML/System/Vector2.hpp>

class BaseLogicalComponent {
public:
    BaseLogicalComponent(std::wstring name, int inputs_count, int outputs_count) :
        m_name(std::move(name)), m_inputs_count(inputs_count), m_outputs_count(outputs_count) {}

    virtual ~BaseLogicalComponent() = default;

    virtual void processInput(const std::vector<bool> *input, std::vector<bool> *output) const = 0;

    [[nodiscard]] inline const std::wstring &getName() const {
        return m_name;
    }

    [[nodiscard]] inline int getInputsCount() const {
        return m_inputs_count;
    }

    [[nodiscard]] inline int getOutputsCount() const {
        return m_outputs_count;
    }

    [[nodiscard]] inline const sf::Vector2f &getSize() const {
        return m_size;
    }

private:
    const std::wstring m_name;
    const int m_inputs_count;
    const int m_outputs_count;
    const sf::Vector2f m_size {100, 100};
};


#endif //LOGICGAMEENGINE_BASELOGICALCOMPONENT_H
