#include "StaticLogicalComponent.h"

StaticLogicalComponent::StaticLogicalComponent(
        const sf::Vector2f &position,
        const BaseLogicalComponent &logical_component_data
) :
        m_shape(logical_component_data.getSize(), position, logical_component_data.getTexture()),
        m_logical_component_data(logical_component_data) {}