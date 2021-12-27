#include "Window.h"

Window::Window() { Setup("Window", sf::Vector2u(640, 480)); }

Window::Window(const std::string &title, const sf::Vector2u &size) {
    Setup(title, size);
}

Window::~Window() { Destroy(); }

void Window::Setup(const std::string &title, const sf::Vector2u &size) {
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullscreen = false;
    m_isDone = false;
    Create();

    m_isFocused = true;
    m_eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullscreen, this);
    m_eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);

    m_window.setFramerateLimit(60);
}

void Window::Create() {
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create(
            {m_windowSize.x, m_windowSize.y, 32},
            m_windowTitle, style
    );
}

void Window::Destroy() {
    m_window.close();
}

void Window::Update() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::LostFocus) {
            m_isFocused = false;
            m_eventManager.SetFocus(false);
        } else if (event.type == sf::Event::GainedFocus) {
            m_isFocused = true;
            m_eventManager.SetFocus(true);
        }
        m_eventManager.HandleEvent(event);
    }
    m_eventManager.Update();
}

void Window::ToggleFullscreen(EventDetails *details) {
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

void Window::BeginDraw() { m_window.clear(sf::Color::White); }

void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() const { return m_isDone; }

bool Window::IsFullscreen() const { return m_isFullscreen; }

sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::Draw(sf::Drawable &drawable) {
    m_window.draw(drawable);
}

bool Window::IsFocused() const { return m_isFocused; }

EventManager *Window::GetEventManager() { return &m_eventManager; }

sf::RenderWindow *Window::GetRenderWindow() { return &m_window; }

void Window::Close(EventDetails *details) { m_isDone = true; }