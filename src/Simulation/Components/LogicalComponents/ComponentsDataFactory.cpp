#include "ComponentsDataFactory.h"

ComponentsDataFactory::ComponentsDataFactory() {
    createComponentsData();
}

const BaseLogicalComponent *ComponentsDataFactory::getComponentData(const std::string &name) {
    if (!m_components.contains(name)) std::cerr << "component named <" << name << "> could not be found" << std::endl;

    return m_components[name];
}

void ComponentsDataFactory::createComponentsData() {
    if (!m_components.empty()) return;

    createComponentData<And>("and");
    createComponentData<Or>("or");
    createComponentData<Not>("not");
    createComponentData<Xor>("xor");
}

ComponentsDataFactory::~ComponentsDataFactory() {
    for (auto const& [name, component] : m_components) {
        delete component;
    }
}
