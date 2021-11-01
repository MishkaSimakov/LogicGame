#ifndef LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
#define LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H

#include "SFML/Graphics.hpp"
#include <string>
#include "Colors.h"

namespace gui {
    class ActingLogicalComponent {
    public:
        ActingLogicalComponent(const sf::Vector2f &position, const std::string &name, bool is_dragged);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

    protected:
        void drawComponent();

        sf::Vector2f m_size;
        sf::Vector2f m_position;
        bool m_is_dragged;

        sf::RectangleShape m_component;
        sf::Text m_name;
    };
}

#endif //LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
