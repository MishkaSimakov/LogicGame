#include "Window.h"

Window::Window(const std::string &title, const sf::Vector2u &size) {
    setup(title, size);
}

Window::~Window() {
    destroy();
}

void Window::setup(const std::string &title, const sf::Vector2u &size) {
    m_window_title = title;
    m_window_size = size;
    m_is_fullscreen = false;
    m_is_done = false;
    create();

    m_event_manager.addEventCallback(StateType(0), sf::Event::Closed, &Window::close, this);
    m_event_manager.addKeyPressedCallback(StateType(0), sf::Keyboard::F5, &Window::toggleFullscreen, this);

    m_window.setFramerateLimit(60);

    m_gui.setTarget(m_window);
    tgui::Theme::setDefault("themes/TransparentGrey.txt");
}

void Window::create() {
    auto style = (m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create(
            {m_window_size.x, m_window_size.y, 32},
            m_window_title, style
    );
}

void Window::destroy() {
    m_window.close();
}

void Window::update() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        m_gui.handleEvent(event);

        m_event_manager.processEvent(event);
    }
}

void Window::toggleFullscreen(const sf::Event &event) {
    m_is_fullscreen = !m_is_fullscreen;
    destroy();
    create();
}

void Window::beginDraw() {
    m_window.clear(sf::Color::White);
}

void Window::endDraw() {
    m_gui.draw();
    m_window.display();
}

bool Window::isDone() const { return m_is_done; }

bool Window::isFullscreen() const { return m_is_fullscreen; }

sf::Vector2u Window::getWindowSize() { return m_window_size; }

void Window::draw(sf::Drawable &drawable) {
    m_window.draw(drawable);
}

EventManager *Window::getEventManager() { return &m_event_manager; }

sf::RenderWindow *Window::getRenderWindow() { return &m_window; }

void Window::close(const sf::Event &event) { m_is_done = true; }
