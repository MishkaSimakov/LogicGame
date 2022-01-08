#ifndef LOGICGAMEENGINE_WINDOW_H
#define LOGICGAMEENGINE_WINDOW_H

#include "Events/EventManager.h"

#include "SFML/Graphics.hpp"
#include <string>
#include <TGUI/Backends/SFML/GuiSFML.hpp>

class Window {
public:
    enum class ViewType {
        DEFAULT,
        SIMULATION
    };

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

    void close();

    void setWindowView(ViewType viewType);

    void setWindowView(const sf::View &view);

    void setView(ViewType viewType, sf::View view);

    sf::View &getView(ViewType viewType);

    tgui::GuiSFML *getGui() {
        return &m_gui;
    }

    sf::Vector2f getMousePosition(ViewType viewType = ViewType::DEFAULT);

    sf::Vector2f getMousePosition(const sf::View &view);

private:
    void handleCloseEvent(const sf::Event &event);

    void setup(const std::string &title, const sf::Vector2u &size);

    void destroy();

    void create();

    sf::RenderWindow m_window;
    sf::Vector2u m_window_size;
    std::string m_window_title;
    bool m_is_done;
    bool m_is_fullscreen;

    EventManager m_event_manager;

    tgui::GuiSFML m_gui;

    std::unordered_map<Window::ViewType, sf::View> m_views;
};


#endif //LOGICGAMEENGINE_WINDOW_H
