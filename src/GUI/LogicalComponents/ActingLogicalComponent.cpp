#include "ActingLogicalComponent.h"

namespace gui {
    ActingLogicalComponent::ActingLogicalComponent(
            const sf::Vector2f &position, const std::string &texture, bool is_dragged
    ) : m_position(position), m_is_dragged(is_dragged), m_size(70, 70) {
        m_component.setTexture(&ResourceHolder::get().textures.get(texture));
        m_component.setSize(m_size);

        m_inputs_count = 2;

        m_inputs.reserve(m_inputs_count);
        for (int i = 0; i < m_inputs_count; ++i) {
            m_inputs.push_back(
                    std::move(std::make_unique<Connector>(this, Connector::type::INPUT, i))
            );
        }

        redraw();
    }

    bool ActingLogicalComponent::handleEvent(sf::Event e, const sf::RenderWindow &window) {
        for (auto &input: m_inputs) {
            input->handleEvent(e, window);

            if (input->m_is_dragging_wire) {
                return true;
            }
        }

        if (m_is_dragged) {
            // move logical component
            if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
                m_is_dragged = false;
            } else if (e.type == sf::Event::MouseMoved) {
                m_position = sf::Vector2f(sf::Mouse::getPosition(window)) - m_size / 2.f;
            }

            redraw();
        } else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            auto pos = sf::Mouse::getPosition(window);

            if (m_component.getGlobalBounds().contains((float) pos.x, (float) pos.y)) {
                m_is_dragged = true;
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
    }

    void ActingLogicalComponent::redraw() {
        m_component.setPosition(m_position);

        for (auto &input: m_inputs) {
            input->redraw();
        }
    }

    Connector *ActingLogicalComponent::tryToConnectWire(Connector *connector, const sf::Vector2f &position) {
        return gui::Simulation::get()->tryToConnectWire(connector, position);
    }

    Connector *ActingLogicalComponent::canConnectWire(Connector *connector, const sf::Vector2f &position) {
        if (connector->m_component == this) {
            return nullptr;
        }

        for (auto &input : m_inputs) {
            if (input->canConnectWire(position)) {
                return input.get();
            }
        }

        return nullptr;
    }
}
