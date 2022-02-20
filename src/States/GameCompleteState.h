#ifndef LOGICGAMEENGINE_GAMECOMPLETESTATE_H
#define LOGICGAMEENGINE_GAMECOMPLETESTATE_H

#include "BaseState.h"
#include "RoundedRectangle.h"

#include <SFML/Graphics.hpp>

class GameCompleteState : public BaseState {
public:
    GameCompleteState(StateManager *stateManager);

    void onCreate() override;

    void onDestroy() override;

    void activate() override;

    void deactivate() override;

    void update(const sf::Time &time) override;

    void draw() override;

protected:
    static float randomFloat();

    void createConfetti(const sf::Vector2f &source_pos, int count, const sf::Vector2f &velocity);

    float m_elapsed{0.f};

    sf::Text m_message;
    RoundedRectangle m_message_background;

    sf::VertexArray m_confetti;
    std::vector<sf::Vector2f> m_confetti_velocity;
    std::vector<sf::Vector2f> m_confetti_generators_pos;
};


#endif //LOGICGAMEENGINE_GAMECOMPLETESTATE_H
