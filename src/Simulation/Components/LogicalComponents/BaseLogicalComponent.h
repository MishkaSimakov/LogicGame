#ifndef LOGICGAMEENGINE_BASELOGICALCOMPONENT_H
#define LOGICGAMEENGINE_BASELOGICALCOMPONENT_H

#include "ResourceHolder.h"

#include <string>
#include <utility>
#include <vector>

class BaseLogicalComponent {
public:
    BaseLogicalComponent(std::wstring name, std::string texture, int inputs_count, int outputs_count) :
        m_name(std::move(name)), m_texture(std::move(texture)), m_inputs_count(inputs_count), m_outputs_count(outputs_count) {}

    virtual void processInput(const std::vector<bool> *input, std::vector<bool> *output) const {};

    inline const std::wstring &getName() const {
        return m_name;
    }

    inline const sf::Texture *getTexture() const {
        return &ResourceHolder::get().textures.get(m_texture);
    }

    inline int getInputsCount() const {
        return m_inputs_count;
    }

    inline int getOutputsCount() const {
        return m_outputs_count;
    }

    inline const sf::Vector2f &getSize() const {
        return m_size;
    }

private:
    const std::wstring m_name;
    const std::string m_texture;
    const int m_inputs_count;
    const int m_outputs_count;
    const sf::Vector2f m_size {100, 100};
};


#endif //LOGICGAMEENGINE_BASELOGICALCOMPONENT_H
