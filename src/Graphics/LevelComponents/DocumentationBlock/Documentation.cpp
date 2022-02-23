#include "Documentation.h"

Documentation::Documentation(
        float max_width, const Level &level, const TextLayout &layout
) :
        m_position(layout.getPosition()),
        m_max_width(max_width),
        m_description(
                layout.getPosition(), layout.getSize().x,
                level.getDescription(), layout.getFontSize()
        ),
        m_truth_table({m_position.x, m_position.y + m_description.getGlobalBounds().height + m_offset}, level) {}

void Documentation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_description);
    target.draw(m_truth_table);
}

void Documentation::update() {
    m_description.setPosition(m_position);
    m_truth_table.setPosition({m_position.x, m_position.y + m_description.getGlobalBounds().height + m_offset});
}

void Documentation::setLevel(const Level &level) {
    m_description.setString(level.getDescription());
    m_truth_table.setLevel(level);
}

sf::FloatRect Documentation::getGlobalBounds() const {
    sf::FloatRect bounds;

    bounds.width = m_max_width;
    bounds.height = m_truth_table.getGlobalBounds().top + m_truth_table.getGlobalBounds().height
                    - m_description.getGlobalBounds().top;
    bounds.left = m_position.x;
    bounds.top = m_position.y;

    return bounds;
}

void Documentation::setPosition(const sf::Vector2f &position) {
    m_position = position;

    update();
}
