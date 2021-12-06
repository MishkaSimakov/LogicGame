#ifndef WIDGET_H
#define WIDGET_H

#include "SFML/Graphics.hpp"

class Widget
{
public:
    virtual bool handleEvent(sf::Event e, const sf::RenderWindow &window) { return false; };
    virtual void render(sf::RenderTarget &renderer) = 0;
};

#endif // WIDGET_H
