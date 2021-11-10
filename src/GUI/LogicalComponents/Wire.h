#ifndef LOGICGAMEENGINE_WIRE_H
#define LOGICGAMEENGINE_WIRE_H

#include "Input.h"
#include "Widget.h"

namespace gui {
    class Wire : public Widget {
    public:
        Wire(Input *input, Input *output);

        virtual void render(sf::RenderTarget &renderer);

    protected:
        Input *m_input;
        Input *m_output;
        sf::RectangleShape m_shape;
    };
}


#endif //LOGICGAMEENGINE_WIRE_H
