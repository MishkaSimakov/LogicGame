#ifndef LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
#define LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H

#include <string>
#include <vector>
#include "Colors.h"
#include "Input.h"

namespace gui {
    class ActingLogicalComponent : public Widget {
    public:
        ActingLogicalComponent(const sf::Vector2f &position, const std::string &name, bool is_dragged);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

        const sf::Vector2f &getSize() const {
            return m_size;
        }

        const sf::Vector2f &getPosition() const {
            return m_position;
        }

        int getInputsCount() const {
            return m_inputs_count;
        }

    protected:
        void redraw();

        sf::Vector2f m_size;
        sf::Vector2f m_position;
        bool m_is_dragged;


        // shapes
        sf::RectangleShape m_component;
        sf::Text m_name;

        // m_inputs
        int m_inputs_count;
        std::vector<Input> m_inputs;
    };
}

#endif //LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
