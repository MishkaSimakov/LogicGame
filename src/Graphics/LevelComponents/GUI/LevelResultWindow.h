#ifndef LOGICGAMEENGINE_LEVELRESULTWINDOW_H
#define LOGICGAMEENGINE_LEVELRESULTWINDOW_H

#include "RoundedRectangle.h"
#include "SharedContext.h"
#include "Window.h"

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

class LevelResultWindow {
public:
    enum class LevelResult {
        SUCCESS,
        PARTIALLY_WRONG,
        TOTALLY_WRONG
    };

    LevelResultWindow(SharedContext *sharedContext, const sf::Vector2f &size, const sf::Vector2f &position);

    void showWithResult(LevelResult result);

    void draw();

protected:
    void hide();

    SharedContext *m_shared_context;
    sf::Vector2f m_size;
    sf::Vector2f m_position;

    LevelResult m_result{LevelResult::SUCCESS};

    bool m_is_opened{false};

    sf::Vector2f m_offset{25.f, 25.f};

    // shapes
    RoundedRectangle m_background;
    sf::RectangleShape m_fade_effect;
    sf::Text m_message;
    tgui::Button::Ptr m_close_btn;
};


#endif //LOGICGAMEENGINE_LEVELRESULTWINDOW_H
