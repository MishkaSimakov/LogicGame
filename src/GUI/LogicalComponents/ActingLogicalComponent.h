#ifndef LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
#define LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H

#include "Widget.h"
#include "Colors.h"
#include "Connector.h"
#include "Simulation.h"
#include "ResourceHolder.h"

#include <memory>
#include <string>
#include <vector>

namespace gui {
    class ActingLogicalComponent : public Widget {
    public:
        ActingLogicalComponent(
                const sf::Vector2f &position,
                const std::string &texture,
                bool is_dragged
        );

        bool handleEvent(sf::Event e, const sf::RenderWindow &window) override;

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

        Connector *tryToConnectWire(Connector *connector, const sf::Vector2f &position);
        Connector *canConnectWire(Connector *connector, const sf::Vector2f &position);

//        void forwardLink(ActingLogicalComponent *another, int output_id) {
//            m_output_components[output_id] = another;
//        }

    protected:
        void redraw();

        sf::Vector2f m_size;
        sf::Vector2f m_position;
        bool m_is_dragged;

        // shapes
        sf::RectangleShape m_component;

        // inputs
        int m_inputs_count;
        std::vector<std::unique_ptr<Connector>> m_inputs;

        // outputs
        int m_outputs_count;
        std::vector<std::unique_ptr<Connector>> m_outputs;

        // links to next components in circuit
        std::vector<ActingLogicalComponent *> m_output_components;
    };
}

#endif //LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
