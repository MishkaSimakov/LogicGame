#include "StateManager.h"

StateManager::StateManager(SharedContext *shared) : m_shared(shared) {
    RegisterState<IntroState>(StateType::MainMenu);
//    RegisterState<State_MainMenu>(StateType::MainMenu);
//    RegisterState<State_Game>(StateType::Game);
//    RegisterState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager() {
    for (auto &state: m_states) {
        state.second->OnDestroy();

        delete state.second;
    }
}

void StateManager::Draw() {
    if (m_states.empty()) {
        return;
    }

    if (m_states.back().second->IsTransparent() && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->IsTransparent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_states.end(); ++itr) {
            itr->second->Draw();
        }
    } else {
        m_states.back().second->Draw();
    }
}

void StateManager::Update(const sf::Time &time) {
    if (m_states.empty()) {
        return;
    }

    if (m_states.back().second->IsTranscendent()
        && m_states.size() > 1) {
        auto itr = m_states.end();
        while (itr != m_states.begin()) {
            if (itr != m_states.end()) {
                if (!itr->second->IsTranscendent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_states.end(); ++itr) {
            itr->second->Update(time);
        }
    } else {
        m_states.back().second->Update(time);
    }
}

SharedContext *StateManager::GetContext() { return m_shared; }

bool StateManager::HasState(StateType type) {
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

void StateManager::Remove(StateType type) {
    m_toRemove.push_back(type);
}

void StateManager::ProcessRequests() {
    while (m_toRemove.begin() != m_toRemove.end()) {
        RemoveState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}

void StateManager::SwitchTo(StateType type) {
    m_shared->m_eventManager->SetCurrentState(type);

    for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) {
        if (itr->first == type) {
            m_states.back().second->Deactivate();
            StateType tmp_type = itr->first;
            BaseState *tmp_state = itr->second;
            m_states.erase(itr);
            m_states.emplace_back(tmp_type, tmp_state);
            tmp_state->Activate();
            return;
        }
    }

    // State with type wasn't found.
    if (!m_states.empty()) {
        m_states.back().second->Deactivate();
    }

    CreateState(type);
    m_states.back().second->Activate();
}

void StateManager::CreateState(StateType type) {
    auto newState = m_stateFactory.find(type);
    if (newState == m_stateFactory.end()) {
        return;
    }

    BaseState *state = newState->second();
    m_states.emplace_back(type, state);
    state->OnCreate();
}

void StateManager::RemoveState(StateType type) {
    for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) {
        if (itr->first == type) {
            itr->second->OnDestroy();
            delete itr->second;
            m_states.erase(itr);
            return;
        }
    }
}