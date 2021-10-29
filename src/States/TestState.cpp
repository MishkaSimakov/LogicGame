#include "TestState.h"

#include <iostream>

TestState::TestState(Game &game) : BaseState(game)
{
    title.setFont(ResourceHolder::get().fonts.get("arial"));

    title.setCharacterSize(24); // in pixels, not points!

    title.setFillColor(sf::Color::Red);
}

void TestState::update(sf::Time delta)
{
    title.setString(std::to_string(delta.asSeconds()));
}

void TestState::render(sf::RenderTarget &renderer)
{
    renderer.draw(title);
}
