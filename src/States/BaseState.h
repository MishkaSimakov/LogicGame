#ifndef LOGICGAMEENGINE_BASESTATE_H
#define LOGICGAMEENGINE_BASESTATE_H

#include <SFML/Graphics.hpp>

class StateManager;

class BaseState {
public:
    BaseState(StateManager *stateManager, bool is_transparent = false, bool is_transcendent = false)
            : m_stateManager(stateManager), m_transparent(is_transparent),
              m_transcendent(is_transcendent) {}

    virtual ~BaseState() {}

    virtual void onCreate() = 0;

    virtual void onDestroy() = 0;

    virtual void activate() = 0;

    virtual void deactivate() = 0;

    virtual void update(const sf::Time &time) = 0;

    virtual void draw() = 0;

    [[nodiscard]] bool isTransparent() const { return m_transparent; }

    [[nodiscard]] bool isTranscendent() const { return m_transcendent; }

    StateManager *getStateManager() { return m_stateManager; }

protected:
    StateManager *m_stateManager;
    bool m_transparent;
    bool m_transcendent;
};

#endif //LOGICGAMEENGINE_BASESTATE_H
