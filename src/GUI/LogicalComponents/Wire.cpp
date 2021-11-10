#include "Wire.h"

namespace gui {

    Wire::Wire(Input *input, Input *output) : m_input(input), m_output(output) {
        m_shape.setFillColor(sf::Color::Black);
        m_shape.setOutlineThickness(0);
    }

//    void Wire::redraw() {
//
//    }

    void Wire::render(sf::RenderTarget &renderer) {

    }
}