#include "Connector.h"

#include "ActingLogicalComponent.h"

namespace gui {
    Connector::Connector(const sf::Vector2f &position, int type) :
            m_position(position),
            m_type(type),
            m_wire(sf::Quads, 4) {
        m_shape.setRadius(5);
        m_shape.setFillColor(gui::colors::light);
        m_shape.setOutlineThickness(2);
        m_shape.setOutlineColor(gui::colors::warning);
        m_shape.setOrigin(5, 5);

        for (int i = 0; i < m_wire.getVertexCount(); ++i) {
            m_wire[i].color = sf::Color::Black;
        }

        redraw();
    }

    void Connector::redraw() {
        m_shape.setPosition(m_position); // set connector position

        if (m_is_dragging_wire || (m_connection && m_type == type::INPUT)) {
            redrawWire();
        }
        if (m_connection) {
            m_connection->redrawWire();
        }
    }

    void Connector::render(sf::RenderTarget &renderer) {
        if (m_is_dragging_wire || (m_connection && m_type == type::INPUT)) {
            renderer.draw(m_wire);
        }

        renderer.draw(m_shape);
    }

    bool Connector::handleEvent(Event e) {
        sf::Vector2f pos(e.getMousePosRelativeTo(Simulation::get()->m_simulation_view));

        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (m_shape.getGlobalBounds().contains(pos)) {
                if (m_connection) {
                    m_connection->setConnection(nullptr);
                    m_connection = nullptr;
                }

                m_is_dragging_wire = true;
                m_temp_wire_end_position = pos;

                redrawWire();

                return true;
            }

            return false;
        } else if (e.type == sf::Event::MouseMoved && m_is_dragging_wire) {
            m_temp_wire_end_position = pos;

            redrawWire();
        } else if (m_is_dragging_wire && e.type == sf::Event::MouseButtonReleased &&
                   e.mouseButton.button == sf::Mouse::Left) {
            m_is_dragging_wire = false;

            m_connection = Simulation::get()->tryToConnectWire(this, m_temp_wire_end_position);

            if (m_connection == nullptr)
                return true;

            m_connection->setConnection(this);
        } else {
            return false;
        }

        return true;
    }

    void Connector::redrawWire() {
        sf::Vector2f a = m_shape.getPosition(), b{0., 0.};

        if (m_is_dragging_wire) {
            b = m_temp_wire_end_position;
        } else if (m_connection != nullptr) {
            b = m_connection->m_shape.getPosition();
        }

        double width = 3;
        double rot = std::atan2(b.x - a.x, b.y - a.y);
        double X1, Y1, X2, Y2;
        X1 = sin(rot + M_PI_2) * (width / 2); // + 90°
        Y1 = cos(rot + M_PI_2) * (width / 2); // + 90°
        X2 = sin(rot + M_PI_2 * 3) * (width / 2); // + 270°
        Y2 = cos(rot + M_PI_2 * 3) * (width / 2); // + 270°

        m_wire[0].position = a + sf::Vector2f(X1, Y1);
        m_wire[1].position = a + sf::Vector2f(X2, Y2);
        m_wire[2].position = b + sf::Vector2f(X2, Y2);
        m_wire[3].position = b + sf::Vector2f(X1, Y1);
    }

    bool Connector::canConnectWire(const sf::Vector2f &position) {
        return m_shape.getGlobalBounds().contains(position);
    }

    bool Connector::getValue() const {
        return m_value;
    }

    void Connector::setValue(bool value, bool t) {
        m_value = value;

        if (m_connection && t) {
            m_connection->setValue(value, false);
        }
    }
}