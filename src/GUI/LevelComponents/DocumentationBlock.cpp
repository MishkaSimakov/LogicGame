#include "DocumentationBlock.h"

namespace gui {

    DocumentationBlock::DocumentationBlock(const std::string &title, const std::string &description, float height) :
            m_background({0, 0}, {200, height}, 10, colors::gray,
                         RoundedRectangle::BOTTOM_RIGHT | RoundedRectangle::TOP_RIGHT) {
//        m_text.setFont(ResourceHolder::get().fonts.get("arial"));
//        m_text.setString("Switch component");
//        m_text.setPosition(10, 10);
//        m_text.setCharacterSize(30);
//        m_text.setFillColor(gui::colors::black);
    }

    void DocumentationBlock::handleEvent(sf::Event e, const sf::RenderWindow &window) {

    }

    void DocumentationBlock::render(sf::RenderTarget &renderer) {
        m_background.render(renderer);
    }
}