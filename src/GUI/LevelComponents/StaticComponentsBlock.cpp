#include "StaticComponentsBlock.h"

gui::StaticComponentsBlock::StaticComponentsBlock() :
        m_background(
                {500, 600},
                {680, 90},
                10,
                colors::gray
        ), m_right_position({510, 610}) {}

bool gui::StaticComponentsBlock::handleEvent(Event e) {
    for (auto &static_logical_component: m_static_logical_components) {
        if (static_logical_component->handleEvent(e))
            return true;
    }

    return false;
}

void gui::StaticComponentsBlock::render(sf::RenderTarget &renderer) {
    m_background.render(renderer);

    for (auto &static_logical_component: m_static_logical_components) {
        static_logical_component->render(renderer);
    }
}

void gui::StaticComponentsBlock::addStaticComponent(BaseLogicalComponent &&logical_component_data) {
    m_static_logical_components.push_back(
            std::move(
                    std::make_unique<StaticLogicalComponent>(m_right_position, logical_component_data)
            )
    );

    m_right_position += {80, 0};
}
