#include "StaticComponentsBlock.h"

StaticComponentsBlock::StaticComponentsBlock(
        const sf::Vector2f &position,
        const sf::Vector2f &size,
        SharedContext *sharedContext
) :
        m_position(position), m_size(size),
        m_background(size, 18), m_shared_context(sharedContext) {
    m_background.setPosition(position);
    m_background.setFillColor(sf::Color(220, 220, 220));
    m_background.setOutlineColor(sf::Color(240, 240, 240));
    m_background.setOutlineThickness(1);
}

void StaticComponentsBlock::draw() {
    m_shared_context->m_wind->draw(m_background);

    for (auto &component: m_components) {
        component->getShape()->draw(m_shared_context->m_wind);
    }
}

void StaticComponentsBlock::addStaticComponent(const BaseLogicalComponent *data) {
    m_components.push_back(
            std::make_unique<StaticLogicalComponent>(nextComponentPosition(), data)
    );
}

sf::Vector2f StaticComponentsBlock::nextComponentPosition() {
    if (m_components.empty()) return m_position + m_offset;

    return m_position + m_offset +
           sf::Vector2f(
                   (float) m_components.size() * (m_components[0]->getShape()->getSize().x + m_space_between),
                   0.f
           );
}

std::optional<std::pair<const BaseLogicalComponent *, sf::Vector2f>>
StaticComponentsBlock::getClickedComponentData(const sf::Vector2f &position) {
    for (auto &component: m_components) {
        if (component->getShape()->checkClick(position)) {
            return std::make_pair(component->getData(), position - component->getShape()->getPosition());
        }
    }

    return {};
}
