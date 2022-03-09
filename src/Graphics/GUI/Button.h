#ifndef LOGICGAMEENGINE_BUTTON_H
#define LOGICGAMEENGINE_BUTTON_H

#include "SharedContext.h"
#include "Window.h"
#include "RoundedRectangle.h"
#include "ResourceHolder.h"
#include "Constants/Paths.h"

#include <string>
#include <array>
#include <SFML/Graphics.hpp>
#include <utility>

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
            std::wstring string = L"",
            ButtonStyle regular_style = {
                    20, sf::Color::Black, 2,
                    sf::Color(200, 200, 200), sf::Color::Black
            },
            ButtonStyle hover_style = {
                    25, sf::Color::Black, 2,
                    sf::Color(210, 210, 210), sf::Color::Black
            },
            ButtonStyle active_style = {
                    25, sf::Color::Black, 2,
                    sf::Color(220, 220, 220), sf::Color::Black
            }
    );

    void setString(const std::wstring &string);

    void setTexture(const sf::Texture *texture);

    void setPosition(const sf::Vector2f &position);

    void setPosition(float x, float y);

    void setVisible(bool is_visible);

    void setEnabled(bool is_enabled);

    template<class T>
    void setOnClickCallback(void(T::*callback)(), T *object) {
        m_on_click_callback = std::bind(callback, object);
    };

    void setOnClickCallback(std::function<void()> callback) {
        m_on_click_callback = std::move(callback);
    }

    sf::Vector2f getSize() {
        return m_size;
    }

    sf::Vector2f getPosition() {
        return m_position;
    }

    void setTextureOffset(float offset);

    void setTextureOffset(float offset_x, float offset_y);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void handleMouseMove(const sf::Event &event);

    void handleMouseButtonPressed(const sf::Event &event);

    void handleMouseButtonReleased(const sf::Event &event);

    bool contains(const sf::Vector2f &position);

    SharedContext *m_shared_context;

    const sf::Texture *m_texture{nullptr};
    sf::Vector2f m_texture_offset{0, 0};

    std::wstring m_string;
    sf::Vector2f m_position;
    sf::Vector2f m_size;

    State m_current_state{State::REGULAR};

    std::array<ButtonStyle, (int) State::STATES_COUNT> m_state_styles;

    RoundedRectangle m_background;
    sf::Sprite m_sprite;
    sf::Text m_label;

    bool m_is_visible{true};
    bool m_is_enabled{true};

    std::function<void()> m_on_click_callback;
};


#endif //LOGICGAMEENGINE_BUTTON_H
