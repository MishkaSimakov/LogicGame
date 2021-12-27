#ifndef LOGICGAMEENGINE_STATEMANAGER_H
#define LOGICGAMEENGINE_STATEMANAGER_H

#include "BaseState.h"

// game states
#include "IntroState.h"

#include "SharedContext.h"
#include <vector>
#include <unordered_map>
#include <functional>

using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState *(void)>>;

class StateManager {
public:
    explicit StateManager(SharedContext *shared);
    ~StateManager();
    void Update(const sf::Time &time);
    void Draw();
    void ProcessRequests();
    SharedContext *GetContext();
    bool HasState(StateType type);
    void SwitchTo(StateType type);
    void Remove(StateType type);
private:
    // Methods.
    void CreateState(StateType type);
    void RemoveState(StateType type);

    template<class T>
    void RegisterState(StateType type) {
        m_stateFactory[type] = [this]() -> BaseState * {
            return new T(this);
        };
    }

    // Members.
    SharedContext *m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};


#endif //LOGICGAMEENGINE_STATEMANAGER_H
