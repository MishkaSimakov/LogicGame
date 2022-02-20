#ifndef LOGICGAMEENGINE_SIMULATIONMANAGER_H
#define LOGICGAMEENGINE_SIMULATIONMANAGER_H

#include "SharedContext.h"
#include "Connector.h"
#include "BaseLogicalComponent.h"
#include "ActingLogicalComponent.h"
#include "WireShape.h"
#include "SimulationConnectorsManager.h"

#include <vector>
#include <memory>
#include <variant>
#include <unordered_set>
#include <exception>

class SimulationManager {
public:
    SimulationManager(SharedContext *sharedContext);

    void update(sf::Time time);

    void draw();

    void handleMousePressed(const sf::Event &event);

    void handleMouseReleased(const sf::Event &event);

    void handleMouseMove(const sf::Event &event);

    void addLogicalComponent(const BaseLogicalComponent *logical_component_data, const sf::Vector2f &position);

    void deleteSelectedShape(const sf::Event &event);

    bool runSimulationTest(const std::vector<bool> &test_inputs, const std::vector<bool> &test_outputs);

    void resetInputs();

protected:
    sf::Vector2f getMousePosition();

    void doSimulationStep();

    void startWireFrom(Connector *connector);

    void drawLogicalComponents();

    void drawWires();

    void drawConnectors();

    void grabComponent(ActingLogicalComponent *component);

    void grabWire(WireShape *wire);

    void grabPlot();

    void dragPlot();

    void releasePlot();

    void dragComponent();

    void dragWire();

    void releaseComponent();

    void releaseWire();

    void deselectShapes();

    void deleteComponentConnector(Connector *connector);

    void deleteComponent(ActingLogicalComponent *component);

    void startSimulation();

    SharedContext *m_shared_context;

    // data for dragging
    ActingLogicalComponent *m_dragged_component{nullptr};
    WireShape *m_dragged_wire{nullptr};
    bool m_is_dragging_plot{false};

    sf::Vector2f m_drag_origin;

    std::vector<Connector *> m_current_connectors;

    std::vector<std::unique_ptr<ActingLogicalComponent>> m_logical_components;
    std::vector<std::unique_ptr<Connector>> m_connectors;
    std::vector<std::unique_ptr<WireShape>> m_wires;

    std::variant<ActingLogicalComponent *, WireShape *> m_selected_shape;

    SimulationConnectorsManager m_simulation_connectors_manager;

    bool m_simulation_running{false};
};


#endif //LOGICGAMEENGINE_SIMULATIONMANAGER_H
