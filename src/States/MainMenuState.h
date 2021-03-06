#ifndef LOGICGAMEENGINE_MAINMENUSTATE_H
#define LOGICGAMEENGINE_MAINMENUSTATE_H

#include "BaseState.h"
#include "Button.h"

#include <SFML/Graphics.hpp>

class MainMenuState : public BaseState {
public:
    explicit MainMenuState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    void startGame();

    void chooseLevel();

    void quitGame();

    sf::Vector2f m_btn_size{400.f, 100.f};
    float m_btn_offset{50.f};

    Button m_start_game_btn;
    Button m_choose_level_btn;
    Button m_quit_game_btn;

    sf::Text m_game_title;
};


#endif //LOGICGAMEENGINE_MAINMENUSTATE_H
