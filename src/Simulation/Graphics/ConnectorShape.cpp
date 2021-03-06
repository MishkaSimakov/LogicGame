#include "ConnectorShape.h"
#include "WireShape.h"
#include "ResourceHolder.h"

void ConnectorShape::update() {
    float radius = m_radius[m_type];
    m_shape.setOrigin(radius, radius);

    m_shape.setRadius(radius);

    if (*m_value_link) {
        m_shape.setFillColor(Constants::Colors::active_connection_color);
    } else {
        m_shape.setFillColor(Constants::Colors::inactive_connection_color);
    }

    m_shape.setPosition(m_position);

    for (auto wire: m_connected_wires) {
        wire->update();
    }

    m_label_shape.setFillColor(Constants::Colors::main_font_color);
    m_label_shape.setString(m_label);
    m_label_shape.setFont(ResourceHolder::get().fonts.get(Constants::Paths::main_font_filename));
    m_label_shape.setCharacterSize(20);
    m_label_shape.setStyle(sf::Text::Bold);

    auto textRect = m_label_shape.getLocalBounds();
    m_label_shape.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
    m_label_shape.setPosition(
            m_position.x,
            m_position.y + radius + 10 + textRect.height / 2.0f
    );

    sf::Vector2f offset{5., 5.};
    m_label_background_shape.setFillColor(sf::Color::White);
    m_label_background_shape.setPosition(sf::Vector2f(m_label_shape.getGlobalBounds().left, m_label_shape.getGlobalBounds().top) - offset);
    m_label_background_shape.setSize({textRect.left + textRect.width + offset.x * 2,
                                      textRect.height + offset.y * 2});
}

void ConnectorShape::draw(Window *window) {
    window->draw(m_shape);

    if (!m_label.empty()) {
        window->draw(m_label_background_shape);
        window->draw(m_label_shape);
    }
}

bool ConnectorShape::checkClick(const sf::Vector2f &position) {
    return m_shape.getGlobalBounds().contains(position);
}

void ConnectorShape::removeConnection(WireShape *wire) {
    auto itr = std::find(m_connected_wires.begin(), m_connected_wires.end(), wire);

    if (itr == m_connected_wires.end()) return;

    m_connected_wires.erase(itr);
}

void ConnectorShape::addConnection(WireShape *wire) {
    m_connected_wires.push_back(wire);
}
