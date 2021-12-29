#include "SimulationManager.h"

SimulationManager::SimulationManager(SharedContext *sharedContext) : m_shared_context(sharedContext) {}

void SimulationManager::draw() {
    drawLogicalComponents();
    drawWires();
    drawConnectors();
}

void SimulationManager::update() {
    //doSimulationStep();
}

void SimulationManager::doSimulationStep() {
    updateCurrentLogicalComponents();

    for (auto logical_component: m_current_logical_components) {
        logical_component->processInputs();
    }
}

void SimulationManager::updateCurrentLogicalComponents() {

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

//    for ()
}

void SimulationManager::handleMouseReleased(const sf::Event &event) {
    if (m_dragged_component) releaseComponent();
    else if (m_dragged_wire) releaseWire();
}

void SimulationManager::handleMouseMove(const sf::Event &event) {
    if (m_dragged_component) dragComponent();
    else if (m_dragged_wire) dragWire();
}

void SimulationManager::addLogicalComponent(const sf::Vector2f &drag_origin, const BaseLogicalComponent &logical_component_data) {
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

            m_dragged_wire = nullptr;

            return;
        }
    }

    // else
    // delete wire from connector
    dragged_wire_origin->getShape()->removeConnection(m_dragged_wire);

    // remove wire from m_wires vector
    for (auto itr = m_wires.begin(); itr != m_wires.end(); itr++) {
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
    return (sf::Vector2f) sf::Mouse::getPosition(*(m_shared_context->m_wind->getRenderWindow()));
}
