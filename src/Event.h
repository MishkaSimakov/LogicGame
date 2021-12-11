#ifndef LOGICGAMEENGINE_EVENT_H
#define LOGICGAMEENGINE_EVENT_H

#include <SFML/Graphics.hpp>

class Event : public sf::Event {
public:
    const sf::RenderWindow &getRenderTarget() const {
        return *m_target;
    }

    void setRenderTarget(sf::RenderWindow &target) {
        m_target = &target;
    }

    sf::Vector2f getMousePosRelativeTo(const sf::View &view) {
        return m_target->mapPixelToCoords(sf::Mouse::getPosition(*m_target), view);
    }

private:
    sf::RenderWindow *m_target;
};


#endif //LOGICGAMEENGINE_EVENT_H
