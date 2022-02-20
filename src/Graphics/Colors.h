#ifndef LOGICGAMEENGINE_COLORS_H
#define LOGICGAMEENGINE_COLORS_H

#include <SFML/Graphics/Color.hpp>

namespace Colors {
    // base elements
    inline const sf::Color BACKGROUND_FILL_COLOR(220, 220, 220);
    inline const sf::Color BACKGROUND_OUTLINE_COLOR(240, 240, 240);

    inline const sf::Color TEXT_FILL_COLOR(sf::Color::Black);

    // wires
    inline const sf::Color SELECTION_COLOR(sf::Color::Black);
    inline const sf::Color WIRE_FILL_COLOR(sf::Color::Black);

    // connectors
    inline const sf::Color CONNECTOR_FILL_COLOR(sf::Color::Black);
    inline const sf::Color CONNECTOR_OUTLINE_COLOR(sf::Color::Black);

    inline const sf::Color SIMULATION_CONNECTOR_FILL_COLOR(sf::Color::Black);
    inline const sf::Color SIMULATION_CONNECTOR_OUTLINE_COLOR(sf::Color::Black);

    // logical components
}

#endif //LOGICGAMEENGINE_COLORS_H
