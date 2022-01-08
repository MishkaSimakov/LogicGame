#include "SimulationConnectorsManager.h"


SimulationConnectorsManager::SimulationConnectorsManager(
        int inputs_count, int outputs_count,
        std::vector<std::unique_ptr<Connector>> *connectors_storage
) : m_inputs_count(inputs_count), m_outputs_count(outputs_count) {
    connectors_storage->reserve(m_inputs_count + m_outputs_count);

    m_inputs.reserve(inputs_count);
    for (int i = 0; i < inputs_count; ++i) {
        auto &connector = connectors_storage->emplace_back(
                std::make_unique<Connector>(Connector::Type::INPUT, true)
        );
        connector->getShape()->setLabel(L"IN");
        m_inputs.push_back(connector.get());

        connector->getShape()->setPosition({900.f + (float) i * 100.f, 100.f});
    }

    m_outputs.reserve(outputs_count);
    for (int i = 0; i < outputs_count; ++i) {
        auto &connector = connectors_storage->emplace_back(
                std::make_unique<Connector>(Connector::Type::OUTPUT, true)
        );
        connector->getShape()->setLabel(L"OUT");
        m_outputs.push_back(connector.get());

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
    for (int i = 0; i < m_outputs_count; ++i) {
        m_outputs[i]->setValue(values[i]);
    }
}

bool SimulationConnectorsManager::checkTest(const std::vector<bool> &test) {
    for (int i = 0; i < m_inputs_count; ++i) {
        if (m_inputs[i]->getValue() != test[i])
            return false;
    }

    return true;
}
