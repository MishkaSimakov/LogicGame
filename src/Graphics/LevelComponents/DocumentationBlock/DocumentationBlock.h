#ifndef LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
#define LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H


#include "ResourceHolder.h"
#include "WrappingText.h"
#include "RoundedRectangle.h"
#include "SharedContext.h"
#include "Window.h"
#include "Button.h"
#include "ScrollBox.h"
#include "LevelLayout.h"
#include "Documentation.h"
#include "Constants/Paths.h"

#include <string>

class DocumentationBlock {
public:
    enum class State {
        FIXED,
        CLOSING,
        OPENING
    };

    DocumentationBlock(
            const Level &level,
            const LevelLayout &layout,
            SharedContext *sharedContext
    );

    void draw();

    void update(const sf::Time &time);

    State getState() const;

    float getPosition() const;

    void setLevel(const Level &level);

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

    SharedContext *m_shared_context;

    RoundedRectangle m_background;
    sf::Text m_title;
    Documentation m_documentation;
    ScrollBox m_description_scroll_box;

    Button m_hide_btn;
    Button m_show_btn;

    State m_state{State::FIXED};

    sf::Vector2f m_animation_offset{0., 0.};

    sf::Int32 m_animation_time{0};

    const LevelLayout &m_layout;
};


#endif //LOGICGAMEENGINE_DOCUMENTATIONBLOCK_H
