#ifndef LOGICGAMEENGINE_EVENT_H
#define LOGICGAMEENGINE_EVENT_H

#include <SFML/Graphics.hpp>

class Event : public sf::Event {
public:
    const sf::Window &getRenderTarget() const {
        return *m_target;
    }

    void setRenderTarget(sf::Window &target) {
        m_target = &target;
    }

private:
    sf::Window *m_target;
};


#endif //LOGICGAMEENGINE_EVENT_H
