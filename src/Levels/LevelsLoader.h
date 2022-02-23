#ifndef LOGICGAMEENGINE_LEVELSLOADER_H
#define LOGICGAMEENGINE_LEVELSLOADER_H

#include "Level.h"

#include <string>
#include <tinyxml2.h>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class LevelsLoader {
public:
    LevelsLoader();

    const std::vector<Level> &getLevels();

    bool checkLevels();

    void loadLevels();

    int getLevelsCount();

    void setLevelPassed(int level_id);

    const char *getLevelsFilename() {
        return m_levels_filename;
    }

protected:
    void loadLevel(tinyxml2::XMLElement *levelElement);

    static void loadTitle(tinyxml2::XMLElement *levelElement, Level *levelData);

    static void loadDescription(tinyxml2::XMLElement *levelElement, Level *levelData);

    static void loadInputsAndOutputs(tinyxml2::XMLElement *levelElement, Level *levelData);

    static void loadAllowedComponents(tinyxml2::XMLElement *levelElement, Level *levelData);

    static void loadTests(tinyxml2::XMLElement *levelElement, Level *levelData);

    std::vector<Level> m_levels;
    const char *m_levels_filename{"resources/levels/levels.xml"};
    tinyxml2::XMLDocument m_levels_file;
};


#endif //LOGICGAMEENGINE_LEVELSLOADER_H
