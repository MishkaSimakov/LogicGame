#ifndef LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
#define LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H

#include "LogicalComponentShape.h"
#include "BaseLogicalComponent.h"
#include "Connector.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

class ActingLogicalComponent {
public:
    ActingLogicalComponent(
            const sf::Vector2f &position, const BaseLogicalComponent *logical_component_data
    );

    // get values from input connectors and send result to output connectors
    void processInputs();

    LogicalComponentShape *getShape() {
        return &m_shape;
    }

    void createConnectors(std::vector<std::unique_ptr<Connector>> &connectors);
    void updateConnectorsPosition();

    std::vector<Connector *> &getInputs() {
        return m_inputs;
    }

    std::vector<Connector *> &getOutputs() {
        return m_outputs;
    }

protected:
    // inputs
    std::vector<Connector *> m_inputs;

    // outputs
    std::vector<Connector *> m_outputs;

    // Logical component data
    const BaseLogicalComponent *m_logical_component_data;

    // object that store all graphical data and handle graphical events for logical component
    LogicalComponentShape m_shape;
};

#endif //LOGICGAMEENGINE_ACTINGLOGICALCOMPONENT_H
