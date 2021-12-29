#ifndef LOGICGAMEENGINE_BASESTATE_H
#define LOGICGAMEENGINE_BASESTATE_H

#include <SFML/Graphics.hpp>

class StateManager;

class BaseState {
public:
    BaseState(StateManager *stateManager)
            : m_stateManager(stateManager), m_transparent(false),
              m_transcendent(false) {}

    virtual ~BaseState() {}

    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void update(const sf::Time &time) = 0;
    virtual void draw() = 0;

    void setTransparent(const bool &transparent) {
        m_transparent = transparent;
    }

    bool isTransparent() const { return m_transparent; }

    void setTranscendent(bool transcendence) {
        m_transcendent = transcendence;
    }

    bool isTranscendent() const { return m_transcendent; }

    StateManager *getStateManager() { return m_stateManager; }

protected:
    StateManager *m_stateManager;
    bool m_transparent;
    bool m_transcendent;
};

#endif //LOGICGAMEENGINE_BASESTATE_H
