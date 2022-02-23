#ifndef LOGICGAMEENGINE_COLORS_H
#define LOGICGAMEENGINE_COLORS_H

#include <SFML/Graphics/Color.hpp>

namespace Constants {
    class Colors {
    public:
        static const sf::Color active_connection_color;
        static const sf::Color inactive_connection_color;

        static const sf::Color selection_outline_color;

        static const sf::Color logical_component_background_color;
        static const sf::Color logical_component_text_color;

        static const sf::Color static_components_block_background_color;
        static const sf::Color static_components_block_outline_color;

        static const sf::Color documentation_background_color;

        static const sf::Color main_font_color;
    };
}


#endif //LOGICGAMEENGINE_COLORS_H
