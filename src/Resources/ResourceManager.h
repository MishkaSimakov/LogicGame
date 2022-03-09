#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Constants/Paths.h"

#include <string>
#include <unordered_map>
#include <iostream>

template<typename Resource>
class ResourceManager {
public:
    ResourceManager(const std::string &folder, const std::string &extention) :
            m_folder(std::string(Constants::Paths::executable_directory) + "resources/" + folder + "/"), m_extention("." + extention) {}

    const Resource &get(const std::string &name) {
        if (!exists(name)) {
            add(name);
        }

        return m_resources.at(name);
    }

    bool exists(const std::string &name) {
        return m_resources.find(name) != m_resources.end();
    }

    void add(const std::string &name) {
        Resource resource;

        if (!resource.loadFromFile(getFullFilename(name))) {
            std::cout << "Error when loading resource called \"" << name << "\"";
        } else {
            m_resources.insert(std::make_pair(name, resource));
        }
    }

private:
    std::string getFullFilename(const std::string &name) {
        return m_folder + name + m_extention;
    }

    const std::string m_folder;
    const std::string m_extention;

    std::unordered_map<std::string, Resource> m_resources;
};

#endif // RESOURCEMANAGER_H
