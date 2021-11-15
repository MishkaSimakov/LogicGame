#ifndef LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
#define LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H

#include <string>
#include <vector>
#include "Colors.h"
#include "Input.h"
#include "Wire.h"
#include <memory>

namespace gui {
    class ActingLogicalComponent : public Widget {
    public:
        ActingLogicalComponent(
                const sf::Vector2f &position,
                bool is_dragged
        );

        void handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void render(sf::RenderTarget &renderer) override;

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

        // m_inputs
        int m_inputs_count;
        std::vector<std::unique_ptr<Input>> m_inputs;
    };
}

#endif //LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
