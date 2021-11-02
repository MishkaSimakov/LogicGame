#ifndef RELATIVEBUTTON_H
#define RELATIVEBUTTON_H

#include "Button.h"

namespace gui {
    class RelativeButton : public Button {
    public:
        RelativeButton(sf::Vector2f pos, sf::Vector2f btn_size, const std::string &text,
                       const sf::RenderWindow &window);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

    private:
        void recalculate(const sf::RenderWindow &window);

        sf::Vector2f m_position;
        sf::Vector2f m_size;
    };
}

#endif // RELATIVEBUTTON_H
