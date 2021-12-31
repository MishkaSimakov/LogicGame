#ifndef LOGICGAMEENGINE_LOGICALCOMPONENTSHAPE_H
#define LOGICGAMEENGINE_LOGICALCOMPONENTSHAPE_H

#include "Window.h"
#include <SFML/Graphics.hpp>

class ActingLogicalComponent;

class LogicalComponentShape {
public:
    enum class ConnectorPlacement {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };

    LogicalComponentShape(
            const sf::Vector2f &size,
            const sf::Vector2f &position,
            const sf::Texture *texture
    ) :
            m_size(size), m_position(position), m_texture(texture) {
        update();
    };

    void draw(Window *window);

    void update();

    void setPosition(const sf::Vector2f &position) {
        m_position = position;

        update();
    }

    const sf::Vector2f &getPosition() const {
        return m_position;
    }

    const sf::Vector2f &getSize() const {
        return m_size;
    }

    sf::Vector2f getConnectorPosition(ConnectorPlacement placement, int connectors_count, int connector_no);

    bool checkClick(const sf::Vector2f &position);

protected:
    const sf::Vector2f m_size;
    sf::Vector2f m_position;

    const sf::Texture *m_texture;
    sf::RectangleShape m_shape;
};


#endif //LOGICGAMEENGINE_LOGICALCOMPONENTSHAPE_H
