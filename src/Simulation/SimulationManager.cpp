#include "SimulationManager.h"

SimulationManager::SimulationManager(SharedContext *sharedContext, int inputs_count, int outputs_count) :
        m_shared_context(sharedContext),
        m_simulation_connectors_manager(inputs_count, outputs_count, &m_connectors) {
    sf::View simulation_view;
    simulation_view.setSize((sf::Vector2f) m_shared_context->m_wind->getWindowSize());
    simulation_view.setCenter((sf::Vector2f) m_shared_context->m_wind->getWindowSize() / 2.f);
    m_shared_context->m_wind->setView(Window::ViewType::SIMULATION, simulation_view);
}

void SimulationManager::draw() {
    m_shared_context->m_wind->setWindowView(Window::ViewType::SIMULATION);

    drawLogicalComponents();
    drawWires();
    drawConnectors();

    m_shared_context->m_wind->setWindowView(Window::ViewType::DEFAULT);
}

void SimulationManager::update(sf::Time time) {
    float movement_speed = 100.f;
    float distance = time.asSeconds() * movement_speed;
    float zoom_factor = 1.01f;

//    std::cout << distance << std::endl;

    sf::View &simulation_view = m_shared_context->m_wind->getView(Window::ViewType::SIMULATION);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        simulation_view.move({0, -distance});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        simulation_view.move({0, distance});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        simulation_view.move({-distance, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        simulation_view.move({distance, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        simulation_view.zoom(zoom_factor);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        simulation_view.zoom(1 / zoom_factor);
    }
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
        m_simulation_running = false;
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

            m_dragged_wire->update();

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
    return m_shared_context->m_wind->getMousePosition(Window::ViewType::SIMULATION);
}

bool SimulationManager::runSimulationTest(const std::vector<bool> &test_inputs, const std::vector<bool> &test_outputs) {
    m_simulation_connectors_manager.setValues(test_inputs);

    m_current_connectors = m_simulation_connectors_manager.getOutputs();
    m_simulation_running = true;

    while (m_simulation_running)
        doSimulationStep();
    
    return m_simulation_connectors_manager.checkTest(test_outputs);
}
