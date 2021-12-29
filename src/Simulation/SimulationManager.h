#ifndef LOGICGAMEENGINE_SIMULATIONMANAGER_H
#define LOGICGAMEENGINE_SIMULATIONMANAGER_H

#include "SharedContext.h"
#include "ActingLogicalComponent.h"
#include "Connector.h"
#include "WireShape.h"

#include <vector>
#include <memory>

class SimulationManager {
public:
    explicit SimulationManager(SharedContext *sharedContext);

    void update();

    void draw();

    void handleMousePressed(const sf::Event &event);

    void handleMouseReleased(const sf::Event &event);

    void handleMouseMove(const sf::Event &event);

    void addLogicalComponent(const sf::Vector2f &drag_origin, const BaseLogicalComponent &logical_component_data);

protected:
    sf::Vector2f getMousePosition();

    void doSimulationStep();

    void startWireFrom(Connector *connector);

    void updateCurrentLogicalComponents();

    void drawLogicalComponents();

    void drawWires();

    void drawConnectors();
    void grabComponent(ActingLogicalComponent *component);

    void dragComponent();
    void dragWire();

    void releaseComponent();
    void releaseWire();

    // data for dragging
    ActingLogicalComponent *m_dragged_component {nullptr};
    WireShape *m_dragged_wire {nullptr};

    sf::Vector2f m_drag_origin;

    std::vector<ActingLogicalComponent *> m_current_logical_components;

    std::vector<std::unique_ptr<ActingLogicalComponent>> m_logical_components;
    std::vector<std::unique_ptr<Connector>> m_connectors;
    std::vector<std::unique_ptr<WireShape>> m_wires;

    SharedContext *m_shared_context;
};


#endif //LOGICGAMEENGINE_SIMULATIONMANAGER_H
