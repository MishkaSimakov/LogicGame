#include "SimulationConnectorsManager.h"


SimulationConnectorsManager::SimulationConnectorsManager(
        const Level *level,
        std::vector<std::unique_ptr<Connector>> *connectors_storage,
        SharedContext *shared_context
) :
        m_inputs_count((int) level->getInputsCount()),
        m_outputs_count((int) level->getOutputsCount()),
        m_shared_context(shared_context) {
    connectors_storage->reserve(m_inputs_count + m_outputs_count);

    m_outputs.reserve(m_outputs_count);
    for (int i = 0; i < m_outputs_count; ++i) {
        auto &connector = connectors_storage->emplace_back(
                std::make_unique<Connector>(ConnectorType::SIMULATION_OUTPUT)
        );
        connector->getShape()->setLabel(level->getOutputs()[i]);
        m_outputs.push_back(connector.get());

        connector->getShape()->setPosition({getConnectorX(i, m_outputs_count),100.f});
    }

    m_inputs.reserve(m_inputs_count);
    for (int i = 0; i < m_inputs_count; ++i) {
        auto &connector = connectors_storage->emplace_back(
                std::make_unique<Connector>(ConnectorType::SIMULATION_INPUT)
        );
        connector->getShape()->setLabel(level->getInputs()[i]);
        m_inputs.push_back(connector.get());

        connector->getShape()->setPosition({getConnectorX(i, m_inputs_count), 700.f});
    }
}

std::vector<Connector *> &SimulationConnectorsManager::getInputs() {
    return m_inputs;
}

std::vector<Connector *> &SimulationConnectorsManager::getOutputs() {
    return m_outputs;
}

void SimulationConnectorsManager::setValues(const std::vector<bool> &values) {
    for (int i = 0; i < m_inputs.size(); ++i) {
        m_inputs[i]->setValue(values[i]);
    }
}

bool SimulationConnectorsManager::checkTest(const std::vector<bool> &test) {
    for (int i = 0; i < m_outputs.size(); ++i) {
        if (m_outputs[i]->getValue() != test[i])
            return false;
    }

    return true;
}

float SimulationConnectorsManager::getConnectorX(int id, int total_count) {
    return ((float) m_shared_context->m_wind->getWindowSize().x + 800 - 100.f * (float) (total_count - 1)) / 2
           + 100.f * (float) id;
}
