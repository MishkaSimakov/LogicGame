#include "SimulationManager.h"

SimulationManager::SimulationManager(SharedContext *sharedContext, int inputs_count, int outputs_count) :
        m_shared_context(sharedContext),
        m_inputs_count(inputs_count),
        m_outputs_count(outputs_count) {
    m_connectors.reserve(inputs_count + outputs_count);

    m_simulation_inputs.reserve(inputs_count);
    for (int i = 0; i < inputs_count; ++i) {
        auto &connector = m_connectors.emplace_back(std::make_unique<Connector>(Connector::Type::INPUT, true));
        m_simulation_inputs.push_back(connector.get());

        connector->getShape()->setPosition({900.f + (float) i * 100.f, 100.f});
    }

    m_simulation_outputs.reserve(outputs_count);
    for (int i = 0; i < outputs_count; ++i) {
        auto &connector = m_connectors.emplace_back(std::make_unique<Connector>(Connector::Type::OUTPUT, true));
        m_simulation_outputs.push_back(connector.get());

        connector->getShape()->setPosition({900.f + (float) i * 100.f, 700.f});
    }
}

void SimulationManager::draw() {
    drawLogicalComponents();
    drawWires();
    drawConnectors();
}

void SimulationManager::update() {

}

void SimulationManager::doSimulationStep() {
    std::unordered_set<ActingLogicalComponent *> temp;

    for (Connector *connector: m_current_connectors) {
        for (Connector *next_connector: connector->getConnections()) {
            next_connector->setValue(connector->getValue());

            if (ActingLogicalComponent *component = next_connector->getComponent()) {
                temp.insert(component);
            }
        }
    }

    if (temp.empty()) {
        stopSimulation();
        return;
    }

    m_current_connectors.clear();
    for (ActingLogicalComponent *component: temp) {
        component->processInputs();

        m_current_connectors.reserve(component->getOutputs().size());
        for (Connector *output: component->getOutputs()) {
            m_current_connectors.push_back(output);
        }
    }
}

void SimulationManager::drawLogicalComponents() {
    for (auto &logical_component: m_logical_components) {
        logical_component->getShape()->draw(m_shared_context->m_wind);
    }
}

void SimulationManager::drawWires() {
    for (auto &wire: m_wires) {
        wire->draw(m_shared_context->m_wind);
    }
}

void SimulationManager::drawConnectors() {
    for (auto &connector: m_connectors) {
        connector->getShape()->draw(m_shared_context->m_wind);
    }
}

void SimulationManager::handleMousePressed(const sf::Event &event) {
    auto position{getMousePosition()};

    for (auto &connector: m_connectors) {
        if (connector->getShape()->checkClick(position)) {
            startWireFrom(connector.get());
            return;
        }
    }

    for (auto &component: m_logical_components) {
        if (component->getShape()->checkClick(position)) {
            grabComponent(component.get());
        }
    }

//    TODO: add wires dragging
}

void SimulationManager::handleMouseReleased(const sf::Event &event) {
    if (m_dragged_component) releaseComponent();
    else if (m_dragged_wire) releaseWire();
}

void SimulationManager::handleMouseMove(const sf::Event &event) {
    if (m_dragged_component) dragComponent();
    else if (m_dragged_wire) dragWire();
}

void SimulationManager::addLogicalComponent(const sf::Vector2f &drag_origin,
                                            const BaseLogicalComponent *logical_component_data) {
    auto &component = m_logical_components.emplace_back(
            std::make_unique<ActingLogicalComponent>(getMousePosition(), logical_component_data)
    );

    component->createConnectors(m_connectors);

    m_drag_origin = drag_origin;
    m_dragged_component = component.get();
}

void SimulationManager::startWireFrom(Connector *connector) {
    if (!connector->canProduceWire()) return;

    WireShape *wire;

    if (connector->getType() == Connector::Type::INPUT) {
        wire = m_wires.emplace_back(std::make_unique<WireShape>(
                getMousePosition(),
                connector->getShape()->getPosition()
        )).get();

        wire->setEndConnector(connector->getShape());
    } else {
        wire = m_wires.emplace_back(std::make_unique<WireShape>(
                connector->getShape()->getPosition(),
                getMousePosition()
        )).get();

        wire->setStartConnector(connector->getShape());
    }

    connector->getShape()->addConnection(wire);
    m_dragged_wire = wire;
}

void SimulationManager::dragComponent() {
    m_dragged_component->getShape()->setPosition(getMousePosition() - m_drag_origin);

    m_dragged_component->updateConnectorsPosition();
}

void SimulationManager::dragWire() {
    m_dragged_wire->dragTo(getMousePosition());
}

void SimulationManager::releaseComponent() {
    m_dragged_component = nullptr;
}

void SimulationManager::releaseWire() {
    // check whether wire under component
    auto mouse_pos{getMousePosition()};
    auto dragged_wire_origin{m_dragged_wire->getDragOriginConnector()->getConnector()};

    for (auto &connector: m_connectors) {
        if (connector->getShape()->checkClick(mouse_pos)
            && connector->canConnectWire(dragged_wire_origin)) {
            // if under component:
            // add connector to wire connections
            m_dragged_wire->addMissingConnector(connector->getShape());

            // add wire to connector shape connections
            connector->getShape()->addConnection(m_dragged_wire);

            // connect connectors one to other and vice versa
            dragged_wire_origin->addConnection(connector.get());
            connector->addConnection(dragged_wire_origin);

            m_dragged_wire = nullptr;

            return;
        }
    }

    // else
    // delete wire from connector
    dragged_wire_origin->getShape()->removeConnection(m_dragged_wire);

    // remove wire from m_wires vector
    for (auto itr = m_wires.cbegin(); itr != m_wires.cend(); itr++) {
        if (itr->get() == m_dragged_wire) {
            m_wires.erase(itr);

            m_dragged_wire = nullptr;

            return;
        }
    }

    // something strange... TODO: add exceptions
}

void SimulationManager::grabComponent(ActingLogicalComponent *component) {
    m_dragged_component = component;
    m_drag_origin = getMousePosition() - component->getShape()->getPosition();
}

sf::Vector2f SimulationManager::getMousePosition() {
    return sf::Vector2f(sf::Mouse::getPosition(*(m_shared_context->m_wind->getRenderWindow())));
}

void SimulationManager::startSimulation() {
    m_simulation_running = true;

    m_current_connectors = m_simulation_outputs;
}

bool SimulationManager::runSimulationTest(bool *test) {
    for (int i = 0; i < m_outputs_count; ++i) {
        m_simulation_outputs[i]->setValue(test[i]);
    }

    startSimulation();

    while (m_simulation_running)
        doSimulationStep();

    for (int i = 0; i < m_inputs_count; ++i) {
        if (m_simulation_inputs[i]->getValue() != test[m_outputs_count + i])
            return false;
    }

    return true;
}
