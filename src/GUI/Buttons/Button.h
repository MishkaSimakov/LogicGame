#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include "ResourceHolder.h"
#include <functional>
#include "Colors.h"

namespace gui {
    class Button : public Widget {
    public:
        Button(
                const sf::Vector2f &position,
                const sf::Vector2f &button_size,
                const std::string &text = "",
                const sf::Color &text_color = gui::colors::black,
                const std::string &font = "arial",
                unsigned int font_size = 30,
                const sf::Color &color = gui::colors::primary,
                float outline_thickness = 0.f,
                const sf::Color &outline_color = gui::colors::dark_primary,
                // effects
                const sf::Color &hover_color = gui::colors::dark_primary,
                const sf::Color &active_color = gui::colors::dark_primary
        );

        virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);

        virtual void render(sf::RenderTarget &renderer);

        void setTexture(const sf::Texture &texture);

        void setCallback(std::function<void(void)> callback);

    protected:
        enum ButtonState {
            NORMAL,
            HOVER,
            ACTIVE
        };

        void updateTextPosition();
        void updateColor(unsigned int state);

        std::function<void(void)> m_callback = []() {};

        sf::RectangleShape m_background;
        sf::Text m_text;

        sf::Color m_background_color;
        sf::Color m_hover_background_color;
        sf::Color m_active_background_color;

        bool m_has_texture = false;
    };
}

#endif // BUTTON_H
