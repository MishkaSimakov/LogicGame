#include "ActingLogicalComponent.h"

ActingLogicalComponent::ActingLogicalComponent(
        const sf::Vector2f &position, const BaseLogicalComponent *logical_component_data
) :
        m_logical_component_data(logical_component_data),
        m_shape(logical_component_data->getSize(), position, logical_component_data->getName()) {}

void ActingLogicalComponent::processInputs() {
    std::vector<bool> inputs;
    inputs.reserve(m_logical_component_data->getInputsCount());

    for (auto &input: m_inputs) {
        inputs.push_back(input->getValue());
    }

    std::vector<bool> outputs;

    outputs.reserve(m_logical_component_data->getOutputsCount());

    m_logical_component_data->processInput(&inputs, &outputs);

    int i = 0;
    for (auto &output: m_outputs) {
        output->setValue(outputs[i]);
        ++i;
    }
}

void ActingLogicalComponent::createConnectors(std::vector<std::unique_ptr<Connector>> &connectors) {
    if (!m_inputs.empty() || !m_outputs.empty()) {
        std::wcerr << L"Повторное создание входов и выходов в логическом компоненте!" << std::endl;
    }

    connectors.reserve(m_logical_component_data->getInputsCount() + m_logical_component_data->getOutputsCount());

    m_inputs.reserve(m_logical_component_data->getInputsCount());
    for (int i = 0; i < m_logical_component_data->getInputsCount(); ++i) {
        auto &connector = connectors.emplace_back(
                std::make_unique<Connector>(
                        ConnectorType::INPUT, this
                )
        );

        m_inputs.insert(m_inputs.begin() + i, connector.get());
    }

    m_outputs.reserve(m_logical_component_data->getOutputsCount());
    for (int i = 0; i < m_logical_component_data->getOutputsCount(); ++i) {
        auto &connector = connectors.emplace_back(
                std::make_unique<Connector>(
                        ConnectorType::OUTPUT, this
                )
        );

        m_outputs.insert(m_outputs.begin() + i, connector.get());
    }

    updateConnectorsPosition();
}

void ActingLogicalComponent::updateConnectorsPosition() {
    for (int i = 0; i < m_logical_component_data->getInputsCount(); ++i) {
        m_inputs[i]->getShape()->setPosition(
                m_shape.getConnectorPosition(
                        LogicalComponentShape::ConnectorPlacement::BOTTOM,
                        m_logical_component_data->getInputsCount(), i
                )
        );
    }

    for (int i = 0; i < m_logical_component_data->getOutputsCount(); ++i) {
        m_outputs[i]->getShape()->setPosition(
                m_shape.getConnectorPosition(
                        LogicalComponentShape::ConnectorPlacement::TOP,
                        m_logical_component_data->getOutputsCount(), i
                )
        );
    }
}
