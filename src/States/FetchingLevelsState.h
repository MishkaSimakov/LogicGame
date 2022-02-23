#ifndef LOGICGAMEENGINE_FETCHINGLEVELSSTATE_H
#define LOGICGAMEENGINE_FETCHINGLEVELSSTATE_H

#include "BaseState.h"
#include <curl/curl.h>
#include <tinyxml2.h>
#include <map>
#include <string>

class FetchingLevelsState : public BaseState {
public:
    explicit FetchingLevelsState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    void fetchLevelsFromServer();

    std::string m_remote_content;
    std::string m_server_url {"http://logics.games/api/level"};

    tinyxml2::XMLDocument m_local_levels_file;
    tinyxml2::XMLDocument m_remote_levels_file;
};


#endif //LOGICGAMEENGINE_FETCHINGLEVELSSTATE_H
