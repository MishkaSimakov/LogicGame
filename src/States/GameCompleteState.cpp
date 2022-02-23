#include "GameCompleteState.h"
#include "ResourceHolder.h"
#include "StateManager.h"

GameCompleteState::GameCompleteState(StateManager *stateManager) :
BaseState(stateManager), m_confetti(sf::Quads) {
    m_message.setString(L"Поздравляем! Вы прошли игру.");
    m_message.setFillColor(sf::Color::Black);
    m_message.setCharacterSize(50);
    m_message.setFont(ResourceHolder::get().fonts.get(Constants::Paths::main_font_filename));

    auto textRect = m_message.getLocalBounds();
    m_message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    auto window_size = stateManager->getContext()->m_wind->getWindowSize();
    m_message.setPosition(sf::Vector2f(window_size / 2u));

    float offset = 50;

    m_message_background.setFillColor(sf::Color(255, 255, 255, 240));
    m_message_background.setOutlineColor(sf::Color(100, 100, 100));
    m_message_background.setOutlineThickness(2);
    m_message_background.setSize(sf::Vector2f(
            m_message.getLocalBounds().width + offset * 2,
            m_message.getLocalBounds().height + offset * 2
    ));
    m_message_background.setOrigin(m_message_background.getSize() / 2.f);
    m_message_background.setPosition(sf::Vector2f(window_size / 2u));

    m_confetti_generators_pos.emplace_back((float) window_size.x / 3, (float) window_size.y);
    m_confetti_generators_pos.emplace_back((float) window_size.x * 2 / 3, (float) window_size.y);
}

void GameCompleteState::onCreate() {
    m_elapsed = 0;
}

void GameCompleteState::onDestroy() {

}

void GameCompleteState::activate() {

}

void GameCompleteState::deactivate() {
    m_confetti_velocity.clear();
    m_confetti.clear();
}

void GameCompleteState::update(const sf::Time &time) {
    m_elapsed += time.asSeconds();

    if (m_elapsed >= 20.0f) {
        m_stateManager->remove(StateType::GameComplete);
        m_stateManager->switchTo(StateType::MainMenu);
    }

    if ((float) m_confetti_velocity.size() < (m_elapsed - 1.f) * 100 / 5) {
        for (auto &generator_position: m_confetti_generators_pos) {
            createConfetti(generator_position, 50, {0, -50});
        }
    }

    for (int i = 0; i < m_confetti_velocity.size(); ++i) {
        m_confetti_velocity[i].y += time.asSeconds() * 5;
        m_confetti_velocity[i].x += (randomFloat() * 5.f - 2.5f) * time.asSeconds();

        m_confetti_velocity[i].y *= powf(0.1f, time.asSeconds());
        m_confetti_velocity[i].x *= powf(0.25f, time.asSeconds());

        m_confetti[i * 4].position += m_confetti_velocity[i];
        m_confetti[i * 4 + 1].position += m_confetti_velocity[i];
        m_confetti[i * 4 + 2].position += m_confetti_velocity[i];
        m_confetti[i * 4 + 3].position += m_confetti_velocity[i];
    }
}

void GameCompleteState::draw() {
    m_stateManager->getContext()->m_wind->draw(m_confetti);

    m_stateManager->getContext()->m_wind->draw(m_message_background);
    m_stateManager->getContext()->m_wind->draw(m_message);
}

void GameCompleteState::createConfetti(const sf::Vector2f &source_pos, int count, const sf::Vector2f &velocity) {
    for (int i = 0; i < count; ++i) {
        sf::Color color((int) (randomFloat() * 255), (int) (randomFloat() * 255), (int) (randomFloat() * 255));

        float m_offset = 30;
        m_confetti.append(sf::Vertex(
                source_pos + sf::Vector2f(randomFloat() * m_offset, randomFloat() * m_offset),
                color
        ));
        m_confetti.append(sf::Vertex(
                source_pos + sf::Vector2f(-randomFloat() * m_offset, randomFloat() * m_offset),
                color
        ));
        m_confetti.append(sf::Vertex(
                source_pos + sf::Vector2f(randomFloat() * m_offset, -randomFloat() * m_offset),
                color
        ));
        m_confetti.append(sf::Vertex(
                source_pos + sf::Vector2f(-randomFloat() * m_offset, -randomFloat() * m_offset),
                color
        ));

        float angle = randomFloat() * 0.5f - 0.25f;
        m_confetti_velocity.emplace_back(sf::Vector2f(
                cos(angle) * velocity.x - sin(angle) * velocity.y + randomFloat() * 40 - 20,
                sin(angle) * velocity.x + cos(angle) * velocity.y + randomFloat() * 40 - 20
        ));
    }
}

float GameCompleteState::randomFloat() {
    return (float) rand() / RAND_MAX;
}
