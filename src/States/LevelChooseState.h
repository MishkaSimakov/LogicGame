#ifndef LOGICGAMEENGINE_LEVELCHOOSESTATE_H
#define LOGICGAMEENGINE_LEVELCHOOSESTATE_H

#include "BaseState.h"
#include "Button.h"

#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class LevelChooseState : public BaseState {
public:
    explicit LevelChooseState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    void choose(int level_id);

    void quitLevelChoose();

    std::vector<std::unique_ptr<Button>> m_level_btns;

    sf::Vector2f m_quit_level_choose_btn_size{50, 50};
    Button m_quit_level_choose_btn;

    int m_max_levels_count_x{8};
    int m_level_count{25};

    sf::Vector2f m_level_btn_size{75.f, 75.f};
    sf::Vector2f m_offset{25.f, 25.f};
};


#endif //LOGICGAMEENGINE_LEVELCHOOSESTATE_H
