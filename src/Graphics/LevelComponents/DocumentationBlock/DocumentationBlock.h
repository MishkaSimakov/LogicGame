#ifndef LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
#define LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H


#include "ResourceHolder.h"
#include "Graphics/WrappingText.h"
#include "RoundedRectangle.h"
#include "SharedContext.h"
#include "Window.h"
#include "Button.h"
#include "ScrollBox.h"

#include <string>
#include <TGUI/TGUI.hpp>

class DocumentationBlock {
public:
    DocumentationBlock(const std::wstring &title, const std::wstring &description, const sf::Vector2f &size,
                       SharedContext *sharedContext);

    void draw();

    void update(const sf::Time &time);

private:
    void updatePositions();

    void show();

    void hide();

    static float easeInOut(float a, float b, float t) {
        if (t <= 0)
            return a;
        else if (t >= 1)
            return b;

        return a + (b - a) * t * t * (3.0f - 2.0f * t);
    }

    sf::Vector2f m_offset{25.f, 25.f};

    RoundedRectangle m_background;
    WrappingText m_title;
    WrappingText m_description;
    ScrollBox m_description_scroll_box;

    SharedContext *m_shared_context;

    Button m_hide_btn;
    Button m_show_btn;

    enum class State {
        FIXED,
        CLOSING,
        OPENING
    };

    State m_state {State::FIXED};

    float m_position;
    float m_opened_position;
    sf::Int32 m_animation_time{0};
};


#endif //LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
