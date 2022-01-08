#ifndef LOGICGAMEENGINE_LEVELRESULTSTATE_H
#define LOGICGAMEENGINE_LEVELRESULTSTATE_H

#include "BaseState.h"
#include "SharedContext.h"
#include "RoundedRectangle.h"
#include "Graphics/GUI/Button.h"
#include "StateManager.h"
#include "Window.h"

class LevelResultState : public BaseState {
public:
    enum class LevelResult {
        SUCCESS,
        PARTIALLY_WRONG,
        TOTALLY_WRONG
    };

    explicit LevelResultState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    void handleSpaceRelease(const sf::Event &event);

    void hide();

    const sf::Vector2f m_size{500.f, 500.f};
    const sf::Vector2f m_close_btn_size{150.f, 40.f};

    sf::Vector2f m_position;

    LevelResult m_result{LevelResult::SUCCESS};

    bool m_is_opened{false};

    sf::Vector2f m_offset{25.f, 25.f};

    // shapes
    RoundedRectangle m_background;
    sf::RectangleShape m_fade_effect;
    sf::Text m_message;
    Button m_close_btn;
};


#endif //LOGICGAMEENGINE_LEVELRESULTSTATE_H
