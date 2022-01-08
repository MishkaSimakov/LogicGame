#ifndef LOGICGAMEENGINE_BUTTON_H
#define LOGICGAMEENGINE_BUTTON_H

#include "SharedContext.h"
#include "Window.h"
#include "RoundedRectangle.h"
#include "ResourceHolder.h"

#include <string>
#include <array>
#include <SFML/Graphics.hpp>

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
            SharedContext *sharedContext, StateType stateType,
            const sf::Vector2f &size, const sf::Vector2f &position = {0, 0},
            std::wstring string = L""
    );

    void setString(const std::wstring &string);

    void setTexture(const sf::Texture *texture);

//    void setSize(const sf::Vector2f &size);

    void setFontSize(float font_size);

    void setPosition(const sf::Vector2f &position);

    void setVisible(bool is_visible);

    void setEnabled(bool is_enabled);

    template<class T>
    void setOnClickCallback(void(T::*callback)(), T *object) {
        m_on_click_callback = std::bind(callback, object);
    };

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void handleMouseMove(const sf::Event &event);

    void handleMouseButtonPressed(const sf::Event &event);

    void handleMouseButtonReleased(const sf::Event &event);

    sf::Vector2f getLabelPosition();

    SharedContext *m_shared_context;

    const sf::Texture *m_texture{nullptr};

    std::wstring m_string;
    sf::Vector2f m_position;
    sf::Vector2f m_size;

    State m_current_state{State::REGULAR};

    std::array<ButtonStyle, (int) State::STATES_COUNT> m_state_styles;

    RoundedRectangle m_background;
    sf::Text m_label;

    bool m_is_visible{true};
    bool m_is_enabled{true};

    std::function<void()> m_on_click_callback;
};


#endif //LOGICGAMEENGINE_BUTTON_H
