#include "DocumentationBlock.h"

DocumentationBlock::DocumentationBlock(
        const std::wstring &title, const std::wstring &description,
        const sf::Vector2f &size, SharedContext *sharedContext
) :
        m_background(
                {0, 0}, size, 18,
                RoundedRectangle::BOTTOM_RIGHT | RoundedRectangle::TOP_RIGHT
        ),
        m_title(m_offset, size.x - m_offset.x * 2, title, 40, "arial", sf::Text::Bold),
        m_description({m_offset.x, 75}, size.x - m_offset.x * 2, description, 30),
        m_shared_context(sharedContext) {
    m_background.setFillColor(sf::Color(220, 220, 220));
    m_background.setOutlineColor(sf::Color(240, 240, 240));
    m_background.setOutlineThickness(1);
}

void DocumentationBlock::draw() {
//    if (m_is_opened) {
    m_shared_context->m_wind->draw(m_background);
    m_shared_context->m_wind->draw(m_title);
    m_shared_context->m_wind->draw(m_description);
//    } else {
    // draw open button
//    }
}
