#ifndef LOGICGAMEENGINE_SIMULATIONMANAGER_H
#define LOGICGAMEENGINE_SIMULATIONMANAGER_H

#include "SharedContext.h"
#include "Connector.h"
#include "BaseLogicalComponent.h"
#include "ActingLogicalComponent.h"
#include "WireShape.h"

#include <vector>
#include <memory>
#include <unordered_set>

class SimulationManager {
public:
    SimulationManager(SharedContext *sharedContext, int inputs_count, int outputs_count);

    void update();

    void draw();

    void handleMousePressed(const sf::Event &event);

    void handleMouseReleased(const sf::Event &event);

    void handleMouseMove(const sf::Event &event);

    void addLogicalComponent(const sf::Vector2f &drag_origin, const BaseLogicalComponent *logical_component_data);

    void startSimulation();

    void stopSimulation() { m_simulation_running = false; };

    bool runSimulationTest(bool *test);

    [[nodiscard]] bool isSimulationRunning() const { return m_simulation_running; };

protected:
    sf::Vector2f getMousePosition();

    void doSimulationStep();

    void startWireFrom(Connector *connector);

    void drawLogicalComponents();

    void drawWires();

    void drawConnectors();

    void grabComponent(ActingLogicalComponent *component);

    void dragComponent();

    void dragWire();

    void releaseComponent();

    void releaseWire();

    SharedContext *m_shared_context;

    // data for dragging
    ActingLogicalComponent *m_dragged_component{nullptr};
    WireShape *m_dragged_wire{nullptr};

    sf::Vector2f m_drag_origin;

    std::vector<Connector *> m_current_connectors;

    std::vector<std::unique_ptr<ActingLogicalComponent>> m_logical_components;
    std::vector<std::unique_ptr<Connector>> m_connectors;
    std::vector<std::unique_ptr<WireShape>> m_wires;

    int m_inputs_count;
    std::vector<Connector *> m_simulation_inputs;

    int m_outputs_count;
    std::vector<Connector *> m_simulation_outputs;

    bool m_simulation_running{false};
};


#endif //LOGICGAMEENGINE_SIMULATIONMANAGER_H
