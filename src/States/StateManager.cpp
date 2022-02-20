#include "StateManager.h"

StateManager::StateManager(SharedContext *shared) : m_shared(shared) {
    registerState<MainMenuState>(StateType::MainMenu);
    registerState<LevelState>(StateType::Level);
    registerState<LevelResultState>(StateType::LevelResult);
    registerState<LevelChooseState>(StateType::LevelChoose);
    registerState<GameCompleteState>(StateType::GameComplete);
    registerState<FetchingLevelsState>(StateType::FetchingLevels);
}

StateManager::~StateManager() {
    for (auto &state: m_states) {
        state.second->onDestroy();

        delete state.second;
    }
}

void StateManager::draw() {
    if (m_states.empty()) {
        return;
    }

    if (m_states.back().second->isTransparent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->isTransparent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_states.end(); ++itr) {
            itr->second->draw();
        }
    } else {
        m_states.back().second->draw();
    }
}

void StateManager::update(const sf::Time &time) {
    if (m_states.empty()) {
        return;
    }

    if (m_states.back().second->isTranscendent()
        && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->isTranscendent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_states.end(); ++itr) {
            itr->second->update(time);
        }
    } else {
        m_states.back().second->update(time);
    }
}

SharedContext *StateManager::getContext() { return m_shared; }

bool StateManager::hasState(StateType type) {
    for (auto &m_state: m_states) {
        if (m_state.first == type) {
            auto removed = std::find(m_toRemove.begin(),
                                     m_toRemove.end(), type);
            if (removed == m_toRemove.end()) { return true; }
            return false;
        }
    }
    return false;
}

void StateManager::remove(StateType type) {
    m_toRemove.push_back(type);
}

void StateManager::processRequests() {
    while (m_toRemove.begin() != m_toRemove.end()) {
        removeState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}

void StateManager::switchTo(StateType type) {
    m_shared->m_eventManager->setCurrentState(type);

    for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) {
        if (itr->first == type) {
            m_states.back().second->deactivate();
            StateType tmp_type = itr->first;
            BaseState *tmp_state = itr->second;
            m_states.erase(itr);
            m_states.emplace_back(tmp_type, tmp_state);
            tmp_state->activate();

            return;
        }
    }

    // State with Type wasn't found.
    if (!m_states.empty()) {
        m_states.back().second->deactivate();
    }

    createState(type);
    m_states.back().second->activate();
}

void StateManager::createState(StateType type) {
    auto newState = m_stateFactory.find(type);
    if (newState == m_stateFactory.end()) {
        return;
    }

    BaseState *state = newState->second();
    m_states.emplace_back(type, state);
    state->onCreate();
}

void StateManager::removeState(StateType type) {
    for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) {
        if (itr->first == type) {
            itr->second->onDestroy();
            delete itr->second;
            m_states.erase(itr);
            return;
        }
    }
}