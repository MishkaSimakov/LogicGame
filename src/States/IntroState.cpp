#include "IntroState.h"
#include "StateManager.h"

void IntroState::OnCreate() {
    m_timePassed = 0.0f;
    sf::Vector2u windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    m_introTexture.loadFromFile("resources/intro.png");
    m_introSprite.setTexture(m_introTexture);
    m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
    m_introSprite.scale({0.5, 0.25});
    m_introSprite.setPosition(windowSize.x / 2.0f, 0);
    m_font.loadFromFile("resources/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString({"Press SPACE to continue"});
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    m_stateManager->GetContext()->m_eventManager
            ->AddCallback(
                    StateType::Intro,
                    "Intro_Continue",
                    &IntroState::Continue,
                    this
            );
}

void IntroState::OnDestroy() {
    m_stateManager->GetContext()->m_eventManager
            ->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void IntroState::Activate() {

}

void IntroState::Deactivate() {

}

void IntroState::Update(const sf::Time &time) {
    if (m_timePassed < 5.0f) {
        m_timePassed += time.asSeconds();
        m_introSprite.setPosition(m_introSprite.getPosition().x,
                                  m_introSprite.getPosition().y + (48 * time.asSeconds()));
    }
}

void IntroState::Draw() {
    m_stateManager->GetContext()->m_wind->GetRenderWindow()->draw(m_introSprite);

    if (m_timePassed >= 5.0f) {
        m_stateManager->GetContext()->m_wind->GetRenderWindow()->draw(m_text);
    }
}

void IntroState::Continue(EventDetails *details) {
    if (m_timePassed >= 5.0f) {
        m_stateManager->SwitchTo(StateType::MainMenu);
        m_stateManager->Remove(StateType::Intro);
    }
}
