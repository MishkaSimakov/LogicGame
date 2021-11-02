#include "DocumentationBlock.h"

namespace gui {

    DocumentationBlock::DocumentationBlock(const std::string &title, const std::string &description, float height) :
            m_background(
                    {0, 0}, {400, height}, 10, colors::gray,
                    RoundedRectangle::BOTTOM_RIGHT | RoundedRectangle::TOP_RIGHT
            ),
            m_title({10, 10}, 400 - 10, title, 30),
            m_description({10, 50}, 400 - 10, description, 15),
            m_hide_button({400 - 10 - 25, 10}, {25, 25}) {
        m_hide_button.setTexture(ResourceHolder::get().textures.get("cross"));
    }

    void DocumentationBlock::handleEvent(sf::Event e, const sf::RenderWindow &window) {

    }

    void DocumentationBlock::render(sf::RenderTarget &renderer) {
        m_background.render(renderer);
        m_title.render(renderer);
        m_description.render(renderer);
        m_hide_button.render(renderer);
    }
}