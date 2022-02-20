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
