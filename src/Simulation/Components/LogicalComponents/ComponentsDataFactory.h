#ifndef LOGICGAMEENGINE_COMPONENTSDATAFACTORY_H
#define LOGICGAMEENGINE_COMPONENTSDATAFACTORY_H

#include "BaseLogicalComponent.h"

#include "And.h"
#include "Or.h"
#include "Not.h"
#include "Xor.h"

#include <map>
#include <string>
#include <iostream>

class ComponentsDataFactory {
public:
    ComponentsDataFactory();

    virtual ~ComponentsDataFactory();

    const BaseLogicalComponent *getComponentData(const std::string &name);

protected:
    void createComponentsData();

    template<class T>
    void createComponentData(std::string name) {
        m_components.emplace(name, new T);
    }

    std::map<std::string, const BaseLogicalComponent *> m_components;
};




#endif //LOGICGAMEENGINE_COMPONENTSDATAFACTORY_H
