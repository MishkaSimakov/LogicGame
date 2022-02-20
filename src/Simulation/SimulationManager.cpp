#include "SimulationManager.h"
#include "StateManager.h"

SimulationManager::SimulationManager(SharedContext *sharedContext) :
        m_shared_context(sharedContext),
        m_simulation_connectors_manager(sharedContext->m_level_manager->getCurrentLevel(), &m_connectors) {
    sf::View simulation_view;
    simulation_view.setSize((sf::Vector2f) m_shared_context->m_wind->getWindowSize());
    simulation_view.setCenter((sf::Vector2f) m_shared_context->m_wind->getWindowSize() / 2.f);
    m_shared_context->m_wind->setView(Window::ViewType::SIMULATION, simulation_view);
}

void SimulationManager::draw() {
    m_shared_context->m_wind->setWindowView(Window::ViewType::SIMULATION);

    drawWires();
    drawLogicalComponents();
    drawConnectors();

    m_shared_context->m_wind->setWindowView(Window::ViewType::DEFAULT);
}

void SimulationManager::update(sf::Time time) {
    float zoom_factor = 1.01f;

    sf::View *simulation_view = m_shared_context->m_wind->getView(Window::ViewType::SIMULATION);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        simulation_view->zoom(zoom_factor);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        simulation_view->zoom(1 / zoom_factor);
    }

    if (m_simulation_running)
        doSimulationStep();
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
            return;
        }
    }

    for (auto &wire: m_wires) {
        if (wire->checkClick(position)) {
            grabWire(wire.get());
            return;
        }
    }

    deselectShapes();

    grabPlot();
}

void SimulationManager::handleMouseReleased(const sf::Event &event) {
    if (m_dragged_component) releaseComponent();
    else if (m_dragged_wire) releaseWire();
    else if (m_is_dragging_plot) releasePlot();
}

void SimulationManager::handleMouseMove(const sf::Event &event) {
    if (m_dragged_component) dragComponent();
    else if (m_dragged_wire) dragWire();
    else if (m_is_dragging_plot) dragPlot();
}

void SimulationManager::addLogicalComponent(
        const BaseLogicalComponent *logical_component_data,
        const sf::Vector2f &position
) {
    auto &component = m_logical_components.emplace_back(
            std::make_unique<ActingLogicalComponent>(position, logical_component_data)
    );

    component->createConnectors(m_connectors);

    grabComponent(component.get());
}

void SimulationManager::startWireFrom(Connector *connector) {
    if (!connector->canProduceWire()) return;

    deselectShapes();

    WireShape *wire;

    if (connector->isInput()) {
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
    if (!m_dragged_wire) return;

    // check whether wire under component
    auto mouse_pos{getMousePosition()};
    auto dragged_wire_origin{m_dragged_wire->getDragOriginConnector()->getConnector()};

    // switch simulation input state
    if (
            dragged_wire_origin->getType() == ConnectorType::SIMULATION_INPUT &&
            dragged_wire_origin->getShape()->checkClick(mouse_pos)
            ) {
        dragged_wire_origin->setValue(!dragged_wire_origin->getValue());

        std::erase_if(
                m_wires,
                [this](auto &other) {
                    return other.get() == m_dragged_wire;
                }
        );

        m_dragged_wire = nullptr;

        startSimulation();

        return;
    }

    for (auto &connector: m_connectors) {
        if (connector->getShape()->checkClick(mouse_pos)
            && connector->canConnectWire(dragged_wire_origin)) {
            // if under component:
            // add connector to wire connections
            m_dragged_wire->addMissingConnector(connector->getShape());

            // add wire to connector shape connections
            connector->getShape()->addConnection(m_dragged_wire);
            dragged_wire_origin->getShape()->addConnection(m_dragged_wire);

            // connect connectors one to other and vice versa
            dragged_wire_origin->addConnection(connector.get());
            connector->addConnection(dragged_wire_origin);

            m_dragged_wire->update();

            m_dragged_wire = nullptr;

            startSimulation();

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
    deselectShapes();

    m_selected_shape = component;
    component->getShape()->select();

    m_dragged_component = component;
    m_drag_origin = getMousePosition() - component->getShape()->getPosition();
}

sf::Vector2f SimulationManager::getMousePosition() {
    return m_shared_context->m_wind->getMousePosition(Window::ViewType::SIMULATION);
}

bool SimulationManager::runSimulationTest(const std::vector<bool> &test_inputs, const std::vector<bool> &test_outputs) {
    m_simulation_connectors_manager.setValues(test_inputs);

    startSimulation();

    while (m_simulation_running)
        doSimulationStep();

    return m_simulation_connectors_manager.checkTest(test_outputs);
}

void SimulationManager::grabWire(WireShape *wire) {
    deselectShapes();

    m_selected_shape = wire;
    wire->select();
}

void SimulationManager::deselectShapes() {
    std::visit([](auto selected_shape) {
        if (selected_shape)
            selected_shape->deselect();
    }, m_selected_shape);

    m_selected_shape = (ActingLogicalComponent *) nullptr;
}

void SimulationManager::deleteSelectedShape(const sf::Event &event) {
    // to prevent deletion of dragged shape
    releaseComponent();
    releaseWire();

    if (std::holds_alternative<ActingLogicalComponent *>(m_selected_shape)) {
        if (auto component = std::get<ActingLogicalComponent *>(m_selected_shape)) {
            deleteComponent(component);
        }
    } else if (std::holds_alternative<WireShape *>(m_selected_shape)) {
        if (auto wire = std::get<WireShape *>(m_selected_shape)) {
            wire->getStartConnector()->getConnector()->removeConnection(
                    wire->getEndConnector()->getConnector()
            );
            wire->getEndConnector()->getConnector()->removeConnection(
                    wire->getStartConnector()->getConnector()
            );

            wire->getStartConnector()->removeConnection(wire);
            wire->getEndConnector()->removeConnection(wire);

            std::erase_if(
                    m_wires,
                    [wire](std::unique_ptr<WireShape> &other) {
                        return wire == other.get();
                    }
            );
        }
    }

    m_selected_shape = (ActingLogicalComponent *) nullptr;
}

void SimulationManager::deleteComponentConnector(Connector *connector) {
    // delete connector - connector link
    for (auto connection: connector->getConnections()) {
        connection->removeConnection(connector);
    }

    // connections must be copied. otherwise, for loop will cause errors
    std::vector<WireShape *> connections = connector->getShape()->getConnections();

    // remove connector shape - connector shape link with wire
    for (auto connection: connections) {
        connection->getStartConnector()->removeConnection(connection);
        connection->getEndConnector()->removeConnection(connection);

        std::erase_if(
                m_wires,
                [connection](auto &other) {
                    return other.get() == connection;
                }
        );
    }

    std::erase_if(
            m_connectors,
            [connector](auto &other) {
                return other.get() == connector;
            }
    );
}

void SimulationManager::grabPlot() {
    m_drag_origin = (sf::Vector2f) sf::Mouse::getPosition();
    m_is_dragging_plot = true;
}

void SimulationManager::dragPlot() {
    m_shared_context->m_wind->getView(Window::ViewType::SIMULATION)
            ->move(
                    (m_drag_origin - (sf::Vector2f) sf::Mouse::getPosition())
                    * m_shared_context->m_wind->getView(Window::ViewType::SIMULATION)->getSize().x
                    / (float) m_shared_context->m_wind->getWindowSize().x
            );

    m_drag_origin = (sf::Vector2f) sf::Mouse::getPosition();
}

void SimulationManager::releasePlot() {
    m_is_dragging_plot = false;
}

void SimulationManager::deleteComponent(ActingLogicalComponent *component) {
    for (auto connector: component->getInputs()) {
        deleteComponentConnector(connector);
    }
    for (auto connector: component->getOutputs()) {
        deleteComponentConnector(connector);
    }

    std::erase_if(
            m_logical_components,
            [component](std::unique_ptr<ActingLogicalComponent> &other) {
                return component == other.get();
            }
    );
}

void SimulationManager::startSimulation() {
    m_current_connectors = m_simulation_connectors_manager.getInputs();
    m_simulation_running = true;
}

void SimulationManager::resetInputs() {
    m_simulation_connectors_manager.setValues(
            std::vector<bool>(m_simulation_connectors_manager.getInputs().size(), false)
    );

    startSimulation();
}
