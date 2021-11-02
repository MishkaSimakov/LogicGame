#include "DocumentationBlock.h"

namespace gui {

    DocumentationBlock::DocumentationBlock(const std::string &title, const std::string &description, float height) :
            m_background(
                    {0, 0}, {400, height}, 10, colors::gray,
                    RoundedRectangle::BOTTOM_RIGHT | RoundedRectangle::TOP_RIGHT
            ),
            m_title({10, 10}, 400 - 10, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer eget augue in turpis scelerisque dictum. Fusce nec lorem erat. Praesent sapien lectus, molestie at enim id, lobortis scelerisque lacus. Vestibulum ac sem eu tortor fermentum malesuada. Nulla egestas, enim non ultrices cursus, lorem diam facilisis tellus, a malesuada tellus arcu quis leo. Suspendisse a laoreet magna. Ut metus enim, feugiat eget condimentum in, tempus at nibh. Sed vel suscipit ipsum, id commodo purus. Pellentesque aliquam condimentum ipsum eget maximus. Nulla congue in ipsum ut tincidunt. Cras mollis leo a turpis volutpat, non gravida velit aliquam. Fusce tempus elit ac nisl ullamcorper ultrices eu at eros.")
            {}

    void DocumentationBlock::handleEvent(sf::Event e, const sf::RenderWindow &window) {

    }

    void DocumentationBlock::render(sf::RenderTarget &renderer) {
        m_background.render(renderer);
        m_title.render(renderer);
    }
}