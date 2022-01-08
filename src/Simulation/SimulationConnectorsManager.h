#ifndef LOGICGAMEENGINE_SIMULATIONCONNECTORSMANAGER_H
#define LOGICGAMEENGINE_SIMULATIONCONNECTORSMANAGER_H

#include "Connector.h"

#include <vector>
#include <memory>

class SimulationConnectorsManager {
public:
    SimulationConnectorsManager(
            int inputs_count, int m_outputs_count,
            std::vector<std::unique_ptr<Connector>> *connectors_storage
    );

    std::vector<Connector *> &getInputs();
    std::vector<Connector *> &getOutputs();

    void setValues(const std::vector<bool> &values);
    bool checkTest(const std::vector<bool> &test);

protected:
    int m_inputs_count;
    int m_outputs_count;

    std::vector<Connector *> m_inputs;
    std::vector<Connector *> m_outputs;
};


#endif //LOGICGAMEENGINE_SIMULATIONCONNECTORSMANAGER_H
