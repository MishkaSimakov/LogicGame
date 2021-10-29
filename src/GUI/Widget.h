#ifndef WIDGET_H
#define WIDGET_H

#include "SFML/Graphics.hpp"

class Widget
{
public:
    virtual void handleEvent(sf::Event e, const sf::RenderWindow &window) = 0;
    virtual void render(sf::RenderTarget &renderer) = 0;
};

#endif // WIDGET_H
