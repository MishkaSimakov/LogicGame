#include "LevelsLoader.h"

LevelsLoader::LevelsLoader() : m_levels_file(true, tinyxml2::COLLAPSE_WHITESPACE) {}

const std::vector<Level> &LevelsLoader::getLevels() {
    if (m_levels.empty()) {
        loadLevels();
    }

    return m_levels;
}

void LevelsLoader::loadLevels() {
    m_levels_file.LoadFile(m_levels_filename);

    auto level = m_levels_file.FirstChildElement("levels")->FirstChildElement();
    for (; level != nullptr; level = level->NextSiblingElement()) {
        loadLevel(level);
    }
}

void LevelsLoader::loadLevel(tinyxml2::XMLElement *levelElement) {
    auto levelData = &m_levels.emplace_back();

    levelData->setPassed(levelElement->BoolAttribute("passed", false));

    loadTitle(levelElement, levelData);
    loadDescription(levelElement, levelData);
    loadInputsAndOutputs(levelElement, levelData);
    loadAllowedComponents(levelElement, levelData);
    loadTests(levelElement, levelData);
}

void LevelsLoader::loadTitle(tinyxml2::XMLElement *levelElement, Level *levelData) {
    auto title = std::string(levelElement->FirstChildElement("title")->GetText());
    levelData->setTitle(sf::String::fromUtf8(title.begin(), title.end()));
}

void LevelsLoader::loadDescription(tinyxml2::XMLElement *levelElement, Level *levelData) {
    auto description = std::string(levelElement->FirstChildElement("description")->GetText());
    levelData->setDescription(sf::String::fromUtf8(description.begin(), description.end()));
}

void LevelsLoader::loadInputsAndOutputs(tinyxml2::XMLElement *levelElement, Level *levelData) {
    auto input = levelElement->FirstChildElement("inputs")->FirstChildElement();

    for (; input != nullptr; input = input->NextSiblingElement()) {
        auto input_name = std::string(input->GetText());
        levelData->appendInput(sf::String::fromUtf8(input_name.begin(), input_name.end()));
    }


    auto output = levelElement->FirstChildElement("outputs")->FirstChildElement();
    for (; output != nullptr; output = output->NextSiblingElement()) {
        auto output_name = std::string(output->GetText());
        levelData->appendOutput(sf::String::fromUtf8(output_name.begin(), output_name.end()));
    }
}

void LevelsLoader::loadTests(tinyxml2::XMLElement *levelElement, Level *levelData) {
    levelData->setVisibleTestsCount(
            levelElement->FirstChildElement("tests")->IntAttribute("visible_count", 0)
    );

    auto test = levelElement->FirstChildElement("tests")->FirstChildElement();

    for (; test != nullptr; test = test->NextSiblingElement()) {
        std::vector<bool> test_inputs;
        std::vector<bool> test_outputs;

        auto test_input_node = test->FirstChildElement("input");

        for (; test_input_node != nullptr; test_input_node = test_input_node->NextSiblingElement("input")) {
            test_inputs.push_back(test_input_node->GetText()[0] == '1');
        }

        auto test_output_node = test->FirstChildElement("output");

        for (; test_output_node != nullptr; test_output_node = test_output_node->NextSiblingElement("output")) {
            test_outputs.push_back(test_output_node->GetText()[0] == '1');
        }

        levelData->appendTest({test_inputs, test_outputs});
    }
}

int LevelsLoader::getLevelsCount() {
    return (int) m_levels.size();
}

void LevelsLoader::setLevelPassed(int level_id) {
    auto level = m_levels_file.FirstChildElement("levels")->FirstChildElement("level");

    for (int i = 0; i < level_id; ++i) {
        level = level->NextSiblingElement();
    }

    std::cout << level_id << " " << level->Attribute("passed") << std::endl;

    level->SetAttribute("passed", true);
    m_levels_file.SaveFile(m_levels_filename);
}

void LevelsLoader::loadAllowedComponents(tinyxml2::XMLElement *levelElement, Level *levelData) {
    auto component = levelElement->FirstChildElement("allowed_components")->FirstChildElement();

    for (; component != nullptr; component = component->NextSiblingElement()) {
        levelData->appendAllowedComponent(component->GetText());
    }
}
