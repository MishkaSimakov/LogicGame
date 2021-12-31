#ifndef LOGICALCOMPONENT_H
#define LOGICALCOMPONENT_H

#include "BaseLogicalComponent.h"
#include "LogicalComponentShape.h"

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

class StaticLogicalComponent {
public:
    StaticLogicalComponent(const sf::Vector2f &position, const BaseLogicalComponent *logical_component_data);

    LogicalComponentShape *getShape() {
        return &m_shape;
    }

    const BaseLogicalComponent *getData() const {
        return m_logical_component_data;
    }

protected:
    LogicalComponentShape m_shape;
    const BaseLogicalComponent *m_logical_component_data;
};

#endif // LOGICALCOMPONENT_H
