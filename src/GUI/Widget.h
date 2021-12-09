#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include "Event.h"

class Widget {
public:
    virtual bool handleEvent(Event e) { return false; };

    virtual void render(sf::RenderTarget &renderer) = 0;
};

#endif // WIDGET_H
