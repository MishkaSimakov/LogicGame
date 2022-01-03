#ifndef LOGICGAMEENGINE_BUTTON_H
#define LOGICGAMEENGINE_BUTTON_H

#include "SharedContext.h"
#include "Window.h"
#include "RoundedRectangle.h"

#include <string>
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>

struct ButtonStyle {
    unsigned int font_size;
    sf::Color font_color;

    float outline_thickness;
    sf::Color fill_color;
    sf::Color outline_color;
};

class Button : public sf::Drawable {
public:
    enum class State {
        REGULAR,
        HOVER,
        ACTIVE,
        STATES_COUNT
    };

    Button(
            SharedContext *sharedContext, const sf::Vector2f &size,
            const sf::Vector2f &position, std::wstring string,
            StateType stateType
    );

    void setString(const std::wstring &string);

    void setSize(const sf::Vector2f &size);

    void setFontSize(float font_size);

    void setPosition(const sf::Vector2f &position);

    void onClick();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void handleMouseMove(const sf::Event &event);

    void handleMouseButtonPressed(const sf::Event &event);

    void handleMouseButtonReleased(const sf::Event &event);

    sf::Vector2f getLabelPosition();

    SharedContext *m_shared_context;

    std::wstring m_string;
    sf::Vector2f m_position;
    sf::Vector2f m_size;

    State m_current_state{State::REGULAR};

    std::array<ButtonStyle, (int) State::STATES_COUNT> m_state_styles;

    RoundedRectangle m_background;
    sf::Text m_label;
};


#endif //LOGICGAMEENGINE_BUTTON_H
