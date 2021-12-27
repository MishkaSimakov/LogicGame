#ifndef LOGICGAMEENGINE_BASELOGICALCOMPONENT_H
#define LOGICGAMEENGINE_BASELOGICALCOMPONENT_H

#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

class BaseLogicalComponent {
public:
    BaseLogicalComponent(std::wstring name, std::string texture, int inputs_count, int outputs_count) :
        m_name(std::move(name)), m_texture(std::move(texture)), m_inputs_count(inputs_count), m_outputs_count(outputs_count) {}

    const std::wstring &getName() const {
        return m_name;
    }

    const sf::Texture *getTexture() const {
        return &ResourceHolder::get().textures.get(m_texture);
    }

    int getInputsCount() const {
        return m_inputs_count;
    }

    int getOutputsCount() const {
        return m_outputs_count;
    }

private:
    const std::wstring m_name;
    const std::string m_texture;
    const int m_inputs_count;
    const int m_outputs_count;
};


#endif //LOGICGAMEENGINE_BASELOGICALCOMPONENT_H
