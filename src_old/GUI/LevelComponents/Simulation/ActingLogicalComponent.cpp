#include "ActingLogicalComponent.h"

namespace gui {
    ActingLogicalComponent::ActingLogicalComponent(
            const sf::Vector2f &position, const BaseLogicalComponent &logical_component_data, bool is_dragged
    ) : m_position(position), m_is_dragged(is_dragged), m_size(70, 70), m_logical_component_data(logical_component_data) {
        m_component.setTexture(m_logical_component_data.getTexture());
        m_component.setSize(m_size);

        m_inputs.reserve(m_logical_component_data.getInputsCount());
        for (int i = 0; i < m_logical_component_data.getInputsCount(); ++i) {
            m_inputs.push_back(
                    std::move(std::make_unique<Connector>(
                            getConnectorPosition(i, Connector::type::INPUT),
                            Connector::type::INPUT
                    ))
            );
        }

        m_outputs.reserve(m_logical_component_data.getOutputsCount());
        for (int i = 0; i < m_logical_component_data.getOutputsCount(); ++i) {
            m_outputs.push_back(
                    std::move(std::make_unique<Connector>(
                            getConnectorPosition(i, Connector::type::OUTPUT),
                            Connector::type::OUTPUT
                    ))
            );
        }

        redraw();
    }

    bool ActingLogicalComponent::handleEvent(Event e) {
        for (auto &input: m_inputs) {
            input->handleEvent(e);

            if (input->m_is_dragging_wire) {
                return true;
            }
        }
        for (auto &output: m_outputs) {
            output->handleEvent(e);

            if (output->m_is_dragging_wire) {
                return true;
            }
        }

        sf::Vector2f pos(e.getMousePosRelativeTo(Simulation::get()->m_simulation_view));

        if (m_is_dragged) {
            // move logical component
            if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
                m_is_dragged = false;

                m_position.x = (float) ((int) m_position.x / 10) * 10;
                m_position.y = (float) ((int) m_position.y / 10) * 10;
            } else if (e.type == sf::Event::MouseMoved) {
                m_position = pos - m_dragging_origin;
            }

            redraw();
        } else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (m_component.getGlobalBounds().contains(pos)) {
                m_is_dragged = true;
                m_dragging_origin = pos - m_position;

                redraw();
            } else {
                return false;
            }
        } else {
            return false;
        }

        return true;
    }

    void ActingLogicalComponent::render(sf::RenderTarget &renderer) {
        renderer.draw(m_component);

        for (auto &input: m_inputs) {
            input->render(renderer);
        }
        for (auto &output: m_outputs) {
            output->render(renderer);
        }
    }

    void ActingLogicalComponent::redraw() {
        m_component.setPosition(m_position);

        for (int i = 0; i < m_logical_component_data.getInputsCount(); ++i) {
            m_inputs[i]->setPosition(getConnectorPosition(i, Connector::type::INPUT));
        }
        for (int i = 0; i < m_logical_component_data.getOutputsCount(); ++i) {
            m_outputs[i]->setPosition(getConnectorPosition(i, Connector::type::OUTPUT));
        }
    }

    Connector *ActingLogicalComponent::checkIfCanConnectWire(Connector *connector, const sf::Vector2f &position) {
        for (auto &c: ((connector->getType() == Connector::type::INPUT) ? m_outputs : m_inputs)) {
            if (c.get() == connector) {
                continue;
            }

            if (c->canConnectWire(position)) {
                return c.get();
            }
        }

        return nullptr;
    }

    sf::Vector2f ActingLogicalComponent::getConnectorPosition(int connector_id, int connector_type) const {
        if (connector_type == Connector::type::INPUT) {
            return {
                    m_size.x / (float) (m_logical_component_data.getInputsCount() + 1) * (float) (connector_id + 1) + m_position.x,
                    m_position.y + m_size.y
            };
        } else if (connector_type == Connector::type::OUTPUT) {
            return {
                    m_size.x / (float) (m_logical_component_data.getOutputsCount() + 1) * (float) (connector_id + 1) + m_position.x,
                    m_position.y
            };
        }

        return {0, 0};
    }
}
