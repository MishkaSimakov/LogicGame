#ifndef LOGICGAMEENGINE_SIMULATIONCONNECTORSMANAGER_H
#define LOGICGAMEENGINE_SIMULATIONCONNECTORSMANAGER_H

#include "Connector.h"
#include "LevelsLoader.h"
#include "Level.h"

#include <vector>
#include <memory>
#include "SharedContext.h"

class SimulationConnectorsManager {
public:
    SimulationConnectorsManager(
            const Level *level,
            std::vector<std::unique_ptr<Connector>> *connectors_storage,
            SharedContext *shared_context
    );

    std::vector<Connector *> &getInputs();

    std::vector<Connector *> &getOutputs();

    void setValues(const std::vector<bool> &values);
    bool checkTest(const std::vector<bool> &test);

protected:
    float getConnectorX(int id, int total_count);

    int m_inputs_count;
    int m_outputs_count;

    std::vector<Connector *> m_inputs;
    std::vector<Connector *> m_outputs;

    SharedContext *m_shared_context;
};


#endif //LOGICGAMEENGINE_SIMULATIONCONNECTORSMANAGER_H
