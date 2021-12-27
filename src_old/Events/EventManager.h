#ifndef LOGICGAMEENGINE_EVENTMANAGER_H
#define LOGICGAMEENGINE_EVENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <utility>

// Code had taken from https://github.com/johnBuffer/SFML-EventManager

// Helper using for shorter types
using EventCallback = std::function<void(const sf::Event &event)>;

template<typename T>
using EventCallbackMap = std::unordered_map<T, EventCallback>;

enum class StateType;

template<typename T>
using Callbacks = std::unordered_map<StateType, EventCallbackMap<T>>;


/*
    This class handles subtyped events like keyboard or mouse events
    The unpack function allows to get relevant information from the processed event
*/
template<typename T>
class SubTypeManager {
public:
    explicit SubTypeManager(std::function<T(const sf::Event &)> unpack) : m_unpack(std::move(unpack)) {}

    ~SubTypeManager() = default;

    void processEvent(StateType state, const sf::Event &event) const {
        T sub_value = m_unpack(event);

        executeCallback(state, sub_value, event);

        // events that must be executed in every state
        executeCallback(StateType(0), sub_value, event);
    }

    template<class T1>
    void addCallback(StateType state, const T &sub_value, void(T1::*func)(const sf::Event &), T1 *instance) {
        m_callbacks[state][sub_value] = std::bind(func, instance, std::placeholders::_1);
    }

private:
    void executeCallback(StateType state, const T &sub_value, const sf::Event &event) const {
        auto event_callbacks_itr(m_callbacks.find(state));
        if (event_callbacks_itr == m_callbacks.end()) {
            return;
        }

        auto callback_itr(event_callbacks_itr->second.find(sub_value));

        if (callback_itr == event_callbacks_itr->second.end()) {
            return;
        }

        callback_itr->second(event);
    }

    Callbacks<T> m_callbacks;
    std::function<T(const sf::Event &)> m_unpack;
};


/*
    This class handles any type of event and call its associated callbacks if any.
    To process key event in a more convenient way its using a KeyManager
*/
class EventManager {
public:
    EventManager() : m_key_pressed_manager([](const sf::Event &event) { return event.key.code; }),
                     m_key_released_manager([](const sf::Event &event) { return event.key.code; }),
                     m_mouse_pressed_manager([](const sf::Event &event) { return event.mouseButton.button; }),
                     m_mouse_released_manager([](const sf::Event &event) { return event.mouseButton.button; }),
                     m_current_state(StateType(0)) {
        // Register key events built in callbacks
        this->addEventCallback(
                StateType(0), sf::Event::EventType::KeyPressed,
                &EventManager::processKeyPressedEvent, this
        );
        this->addEventCallback(
                StateType(0), sf::Event::EventType::KeyReleased,
                &EventManager::processKeyReleasedEvent, this
        );
        this->addEventCallback(
                StateType(0), sf::Event::EventType::MouseButtonPressed,
                &EventManager::processMousePressedEvent, this
        );
        this->addEventCallback(
                StateType(0), sf::Event::EventType::MouseButtonReleased,
                &EventManager::processMouseReleasedEvent, this
        );
    }

    // Calls events' attached callbacks
    void processEvent(const sf::Event &event) const {
        executeCallback(m_current_state, event);

        executeCallback(StateType(0), event);
    }

    void setCurrentState(StateType state) {
        m_current_state = state;
    }

    // Attaches new callback to an event
    template<class T1>
    void
    addEventCallback(StateType state, sf::Event::EventType type, void(T1::*func)(const sf::Event &), T1 *instance) {
        m_events_callbacks[state][type] = std::bind(func, instance, std::placeholders::_1);
    }

    // Adds a key pressed callback
    template<class T1>
    void addKeyPressedCallback(StateType state, sf::Keyboard::Key key_code, void(T1::*func)(const sf::Event &),
                               T1 *instance) {
        m_key_pressed_manager.addCallback(state, key_code, func, instance);
    }

    // Adds a key released callback
    template<class T1>
    void addKeyReleasedCallback(StateType state, sf::Keyboard::Key key_code, void(T1::*func)(const sf::Event &),
                                T1 *instance) {
        m_key_released_manager.addCallback(state, key_code, func, instance);
    }

    // Adds a mouse pressed callback
    template<class T1>
    void addMousePressedCallback(StateType state, sf::Mouse::Button button, void(T1::*func)(const sf::Event &),
                                 T1 *instance) {
        m_mouse_pressed_manager.addCallback(state, button, func, instance);
    }

    // Adds a mouse released callback
    template<class T1>
    void addMouseReleasedCallback(StateType state, sf::Mouse::Button button, void(T1::*func)(const sf::Event &),
                                  T1 *instance) {
        m_mouse_released_manager.addCallback(state, button, func, instance);
    }

private:
    void processKeyPressedEvent(const sf::Event &event) {
        m_key_pressed_manager.processEvent(m_current_state, event);
    }

    void processKeyReleasedEvent(const sf::Event &event) {
        m_key_released_manager.processEvent(m_current_state, event);
    }

    void processMousePressedEvent(const sf::Event &event) {
        m_mouse_pressed_manager.processEvent(m_current_state, event);
    }

    void processMouseReleasedEvent(const sf::Event &event) {
        m_mouse_released_manager.processEvent(m_current_state, event);
    }

    // Runs the callback associated with an event
    void executeCallback(StateType state, const sf::Event &e) const {
        auto event_callbacks_itr(m_events_callbacks.find(state));
        if (event_callbacks_itr == m_events_callbacks.end()) {
            return;
        }

        auto callback_itr(event_callbacks_itr->second.find(e.type));

        if (callback_itr == event_callbacks_itr->second.end()) {
            return;
        }

        callback_itr->second(e);
    }

    SubTypeManager<sf::Keyboard::Key> m_key_pressed_manager;
    SubTypeManager<sf::Keyboard::Key> m_key_released_manager;
    SubTypeManager<sf::Mouse::Button> m_mouse_pressed_manager;
    SubTypeManager<sf::Mouse::Button> m_mouse_released_manager;
    Callbacks<sf::Event::EventType> m_events_callbacks;

    StateType m_current_state;
};

#endif //LOGICGAMEENGINE_EVENTMANAGER_H
