#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include "ResourceHolder.h"
#include <functional>
#include "Colors.h"

namespace gui
{
class Button : public Widget
{
public:
    Button();
    Button(const sf::Vector2f &posision, const sf::Vector2f &button_size, const std::string &text);

    virtual void handleEvent(sf::Event e, const sf::RenderWindow &window);
    virtual void render(sf::RenderTarget &renderer);

    void setPosition(const sf::Vector2f &pos);
    void setSize(const sf::Vector2f &button_size);

    void setText(const std::string &text);

    void setCallback(std::function<void(void)> callback);
protected:
    void updateText();
    std::function<void(void)> m_callback = []() {};

    sf::RectangleShape m_button;
    sf::Text m_text;
};
}

#endif // BUTTON_H
