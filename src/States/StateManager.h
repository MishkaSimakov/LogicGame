#ifndef LOGICGAMEENGINE_STATEMANAGER_H
#define LOGICGAMEENGINE_STATEMANAGER_H


#include "BaseState.h"

// game states
#include "MainMenuState.h"
#include "LevelState.h"
#include "LevelResultState.h"

#include "SharedContext.h"

#include <vector>
#include <unordered_map>
#include <functional>

enum class StateType {
    MainMenu = 1, Level, LevelResult
};

using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState *(void)>>;

class StateManager {
public:
    explicit StateManager(SharedContext *shared);
    ~StateManager();
    void update(const sf::Time &time);
    void draw();
    void processRequests();
    SharedContext *getContext();
    bool hasState(StateType type);
    void switchTo(StateType type);
    void remove(StateType type);
private:
    // Methods.
    void createState(StateType type);
    void removeState(StateType type);

    template<class T>
    void registerState(StateType type) {
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
