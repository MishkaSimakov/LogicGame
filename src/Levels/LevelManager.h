#ifndef LOGICGAMEENGINE_LEVELMANAGER_H
#define LOGICGAMEENGINE_LEVELMANAGER_H

#include "LevelsLoader.h"
#include "Level.h"

#include <string>
#include <map>

class LevelManager {
public:
    enum class LevelResult {
        SUCCESS = 0,
        PARTIALLY_WRONG = 1,
        TOTALLY_WRONG = 2
    };

    LevelManager() {
        m_result_percentages[LevelResult::SUCCESS] = 1.f;
        m_result_percentages[LevelResult::PARTIALLY_WRONG] = 0.75f;
        m_result_percentages[LevelResult::TOTALLY_WRONG] = 0.f;
    };

    const Level *getCurrentLevel() {
        return &m_levels_loader.getLevels()[m_current_level_id];
    }

    void nextLevel() {
        ++m_current_level_id;
    }

    void setCurrentLevel(int level_id) {
        m_current_level_id = level_id;
    }

    bool isCurrentLevelPassed() {
        return m_passed_tests_count == getCurrentLevel()->getTests().size();
    }

    int getPassedTestsCount() const {
        return m_passed_tests_count;
    }

    void setPassedTestsCount(int passed_tests_count) {
        m_passed_tests_count = passed_tests_count;

        if (isCurrentLevelPassed()) {
            m_levels_loader.setLevelPassed(m_current_level_id);
        }
    }

    LevelResult getResult() {
        float percentage = (float) m_passed_tests_count / (float) getCurrentLevel()->getTests().size();

        for (auto[level_result, result_threshold]: m_result_percentages) {
            if (percentage >= result_threshold)
                return level_result;
        }

        return LevelResult::TOTALLY_WRONG;
    }

    int getCurrentLevelId() const {
        return m_current_level_id;
    }

    const std::vector<Level> &getLevels() {
        return m_levels_loader.getLevels();
    }

    void loadLevels() {
        m_levels_loader.getLevels(); // levels will be loaded when first getLevels called
    }

    bool checkLevels() {
        return m_levels_loader.checkLevels(); // check if levels file correct
    }

    bool isLevelUnlocked(int level_id) {
        return level_id == 0 || m_levels_loader.getLevels()[level_id - 1].isPassed();
    }

    bool hasNextLevel() {
        return m_current_level_id != m_levels_loader.getLevelsCount() - 1;
    }

    const char *getLevelsFilename() {
        return m_levels_loader.getLevelsFilename();
    }

protected:
    int m_current_level_id{0};
    int m_passed_tests_count{0};

    LevelsLoader m_levels_loader;

    std::map<LevelResult, float> m_result_percentages;
};


#endif //LOGICGAMEENGINE_LEVELMANAGER_H
