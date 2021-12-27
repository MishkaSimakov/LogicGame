#ifndef LOGICGAMEENGINE_INTROSTATE_H
#define LOGICGAMEENGINE_INTROSTATE_H

#include "BaseState.h"
#include "EventManager.h"
#include <SFML/Graphics.hpp>

class IntroState : public BaseState {
public:
    IntroState(StateManager *stateManager) : BaseState(stateManager) {}

    void OnCreate() override;
    void OnDestroy() override;
    void Activate() override;
    void Deactivate() override;
    void Update(const sf::Time &time) override;
    void Draw() override;

    void Continue(EventDetails *details);
private:
    sf::Texture m_introTexture;
    sf::Sprite m_introSprite;
    sf::Font m_font;
    sf::Text m_text;
    float m_timePassed;
};


#endif //LOGICGAMEENGINE_INTROSTATE_H
