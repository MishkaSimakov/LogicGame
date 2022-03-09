#include "LogicalComponentShape.h"

LogicalComponentShape::LogicalComponentShape(
        const sf::Vector2f &size, const sf::Vector2f &position,
        const std::wstring &name
) : m_size(size),
    m_position(position) {
    m_shape.setSize(m_size);
//    m_shape.setTexture(m_texture);
    m_shape.setFillColor(sf::Color(19, 60, 85));

    m_text.setFont(ResourceHolder::get().fonts.get(Constants::Paths::main_font_filename));
    m_text.setString(name);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(40);

    auto textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);

    update();
}

void LogicalComponentShape::draw(Window *window) {
    window->draw(m_shape);
    window->draw(m_text);
}

void LogicalComponentShape::update() {
    m_shape.setPosition(m_position);
    m_text.setPosition(
            m_position + m_size / 2.f
    );

    if (m_selected) {
        m_shape.setOutlineThickness(10);
        m_shape.setOutlineColor(sf::Color(100, 100, 100, 50));
    } else {
        m_shape.setOutlineThickness(0);
    }
}

sf::Vector2f LogicalComponentShape::getConnectorPosition(
        ConnectorPlacement placement,
        int connectors_count,
        int connector_no
) {
    if (placement == ConnectorPlacement::TOP) {
        return m_position + sf::Vector2f(m_size.x / (float) (connectors_count + 1) * (float) (connector_no + 1), .0f);
    } else if (placement == ConnectorPlacement::BOTTOM) {
        return m_position +
               sf::Vector2f(m_size.x / (float) (connectors_count + 1) * (float) (connector_no + 1), m_size.y);
    }

    return m_position;
}

bool LogicalComponentShape::checkClick(const sf::Vector2f &position) {
    return m_shape.getGlobalBounds().contains(position);
}

