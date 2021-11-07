#ifndef LOGICGAMEENGINE_INPUT_H
#define LOGICGAMEENGINE_INPUT_H

#include "Widget.h"

namespace gui {
    class ActingLogicalComponent;

    class Input : public Widget {
    public:
        Input(ActingLogicalComponent *component, int position);

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

        void redraw(ActingLogicalComponent *component);

        enum type {
            INPUT = 0,
            OUTPUT = 1
        };

    protected:
        bool m_type;
        int m_id;

        sf::CircleShape m_shape;
    };
}

#endif //LOGICGAMEENGINE_INPUT_H
