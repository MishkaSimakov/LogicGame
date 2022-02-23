#include "StaticComponentsBlock.h"

StaticComponentsBlock::StaticComponentsBlock(
        const sf::Vector2f &position,
        const sf::Vector2f &size,
        SharedContext *sharedContext
) :
        m_position(position), m_size(size), m_shared_context(sharedContext) {
    m_background.setCornerRadius(18.f);
    m_background.setFillColor(Constants::Colors::static_components_block_background_color);
    m_background.setOutlineColor(Constants::Colors::static_components_block_outline_color);
    m_background.setOutlineThickness(1);

    m_background.setSize(m_size);
    m_background.setPosition(m_position);

    update();
}

void StaticComponentsBlock::draw() {
    m_shared_context->m_wind->draw(m_background);

    for (auto &component: m_components) {
        component->getShape()->draw(m_shared_context->m_wind);
    }
}

void StaticComponentsBlock::clearStaticComponents() {
    m_components.clear();
}

void StaticComponentsBlock::addStaticComponent(const BaseLogicalComponent *data) {
    m_components.push_back(
            std::make_unique<StaticLogicalComponent>(
                    getNextComponentPosition(),
                    data
            )
    );
}

sf::Vector2f StaticComponentsBlock::getNextComponentPosition() {
    if (m_components.empty()) return m_position + m_offset;

    return getComponentPosition((int) m_components.size());
}

sf::Vector2f StaticComponentsBlock::getComponentPosition(int n) {
    float x_offset = 0;
    for (int i = 0; i < n; ++i) {
        x_offset += m_components[i]->getShape()->getSize().x + m_space_between;
    }

    return m_position + m_offset + sf::Vector2f(x_offset, 0.f);
}

std::optional<std::pair<const BaseLogicalComponent *, const sf::Vector2f &>>
StaticComponentsBlock::getClickedComponentData(const sf::Vector2f &position) {
    for (auto &component: m_components) {
        if (component->getShape()->checkClick(position)) {
            return std::make_pair(
                    component->getData(),
                    m_shared_context->m_wind->getRenderWindow()->mapPixelToCoords(
                            (sf::Vector2i) component->getShape()->getPosition(),
                            *m_shared_context->m_wind->getView(Window::ViewType::SIMULATION)
                    )
            );
        }
    }

    return {};
}

void StaticComponentsBlock::setPosition(const sf::Vector2f &position) {
    m_position = position;

    update();
}

void StaticComponentsBlock::setSize(const sf::Vector2f &size) {
    m_size = size;

    update();
}

void StaticComponentsBlock::update() {
    m_background.setSize(m_size);
    m_background.setPosition(m_position);

    for (int i = 0; i < m_components.size(); ++i) {
        m_components[i]->getShape()->setPosition(getComponentPosition(i));
    }
}

const sf::Vector2f &StaticComponentsBlock::getSize() const {
    return m_size;
}
