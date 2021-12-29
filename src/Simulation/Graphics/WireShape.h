#ifndef LOGICGAMEENGINE_WIRESHAPE_H
#define LOGICGAMEENGINE_WIRESHAPE_H

#include "Window.h"
#include "ConnectorShape.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class WireShape {
public:
    WireShape(const sf::Vector2f &start, const sf::Vector2f &end) :
            m_start(start), m_end(end), m_shape(sf::Quads, 4) {};

    void setStartConnector(ConnectorShape *start_connector) {
        m_start_connector = start_connector;
    }

    void setEndConnector(ConnectorShape *end_connector) {
        m_end_connector = end_connector;
    }

    // Эта функция в случае, когда кабель перемещают, возвращает коннектор из которого его тянут
    ConnectorShape *getDragOriginConnector();

    void addMissingConnector(ConnectorShape *connector);

    void draw(Window *window);

    void update();

    void dragTo(const sf::Vector2f &position);

protected:
    ConnectorShape *m_start_connector{nullptr};
    ConnectorShape *m_end_connector{nullptr};

    sf::VertexArray m_shape;

    sf::Vector2f m_start;
    sf::Vector2f m_end;
};


#endif //LOGICGAMEENGINE_WIRESHAPE_H
