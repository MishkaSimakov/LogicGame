#ifndef LOGICGAMEENGINE_LEVELRESULTSTATE_H
#define LOGICGAMEENGINE_LEVELRESULTSTATE_H

#include "BaseState.h"
#include "SharedContext.h"
#include "RoundedRectangle.h"
#include "Button.h"
#include "StateManager.h"
#include "Window.h"
#include "LevelManager.h"
#include "Constants/Paths.h"
#include "Constants/Colors.h"

#include <string>
#include <unordered_map>
#include <vector>

class LevelResultState : public BaseState {
public:
    explicit LevelResultState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    void hide();

    void nextLevel();

    const sf::Vector2f m_size{500.f, 500.f};
    const sf::Vector2f m_close_btn_size{150.f, 40.f};
    const sf::Vector2f m_next_level_btn_size{275.f, 40.f};

    sf::Vector2f m_position;

    std::unordered_map<LevelManager::LevelResult, std::wstring> m_result_messages;

    sf::Vector2f m_offset{25.f, 25.f};

    // shapes
    RoundedRectangle m_background;
    sf::RectangleShape m_fade_effect;
    sf::Text m_message;
    sf::Text m_submessage;
    Button m_close_btn;
    Button m_next_level_btn;
};


#endif //LOGICGAMEENGINE_LEVELRESULTSTATE_H
