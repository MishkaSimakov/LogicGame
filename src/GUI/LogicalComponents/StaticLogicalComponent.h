#ifndef LOGICALCOMPONENT_H
#define LOGICALCOMPONENT_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "Colors.h"
#include "ActingLogicalComponent.h"

namespace gui {
    class StaticLogicalComponent {
    public:
        StaticLogicalComponent(const sf::Vector2f &position, const std::string &name,
                               std::vector<ActingLogicalComponent> *acting_components_list);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

    protected:
        sf::RectangleShape m_component;
        sf::Text m_name;
        std::vector<ActingLogicalComponent> *m_acting_components_list;
    };
}

#endif // LOGICALCOMPONENT_H
