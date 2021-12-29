#ifndef LOGICGAMEENGINE_WINDOW_H
#define LOGICGAMEENGINE_WINDOW_H

#include "Events/EventManager.h"

#include "SFML/Graphics.hpp"
#include <string>

class Window {
public:
    Window(const std::string &title, const sf::Vector2u &size);

    ~Window();

    void beginDraw(); // Clear the window.
    void endDraw(); // Display the changes.

    void update();

    bool isDone() const;

    bool isFullscreen() const;

    sf::Vector2u getWindowSize();

    void draw(sf::Drawable &drawable);

    EventManager *getEventManager();

    sf::RenderWindow *getRenderWindow();

    void toggleFullscreen(const sf::Event &event);

    void close(const sf::Event &event);

private:
    void setup(const std::string &title, const sf::Vector2u &size);

    void destroy();

    void create();

    sf::RenderWindow m_window;
    sf::Vector2u m_window_size;
    std::string m_window_title;
    bool m_is_done;
    bool m_is_fullscreen;

    EventManager m_event_manager;
};


#endif //LOGICGAMEENGINE_WINDOW_H
