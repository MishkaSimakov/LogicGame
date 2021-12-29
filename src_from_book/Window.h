#ifndef LOGICGAMEENGINE_WINDOW_H
#define LOGICGAMEENGINE_WINDOW_H

#include "Events/EventManager.h"

#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
    Window();
    Window(const std::string &title, const sf::Vector2u &size);
    ~Window();

    void BeginDraw(); // Clear the window.
    void EndDraw(); // Display the changes.

    void Update();
    bool IsDone() const;
    bool IsFullscreen() const;
    sf::Vector2u GetWindowSize();
    void Draw(sf::Drawable &drawable);

    bool IsFocused() const;
    EventManager *GetEventManager();
    sf::RenderWindow *GetRenderWindow();
    void ToggleFullscreen(EventDetails *details);
    void Close(EventDetails *details);
private:
    void Setup(const std::string &title, const sf::Vector2u &size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;

    EventManager m_eventManager;
    bool m_isFocused;
};


#endif //LOGICGAMEENGINE_WINDOW_H
