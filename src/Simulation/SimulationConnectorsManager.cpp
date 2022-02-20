#include "SimulationConnectorsManager.h"


SimulationConnectorsManager::SimulationConnectorsManager(
        const Level *level,
        std::vector<std::unique_ptr<Connector>> *connectors_storage
) : m_inputs_count(level->getInputsCount()), m_outputs_count(level->getOutputsCount()) {
    connectors_storage->reserve(m_inputs_count + m_outputs_count);

    m_outputs.reserve(m_outputs_count);
    for (int i = 0; i < m_outputs_count; ++i) {
        auto &connector = connectors_storage->emplace_back(
                std::make_unique<Connector>(ConnectorType::SIMULATION_OUTPUT)
        );
        connector->getShape()->setLabel(level->getOutputs()[i]);
        m_outputs.push_back(connector.get());

        connector->getShape()->setPosition({900.f + (float) i * 100.f, 100.f});
    }

    m_inputs.reserve(m_inputs_count);
    for (int i = 0; i < m_inputs_count; ++i) {
        auto &connector = connectors_storage->emplace_back(
                std::make_unique<Connector>(ConnectorType::SIMULATION_INPUT)
        );
        connector->getShape()->setLabel(level->getInputs()[i]);
        m_inputs.push_back(connector.get());

        connector->getShape()->setPosition({900.f + (float) i * 100.f, 700.f});
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
