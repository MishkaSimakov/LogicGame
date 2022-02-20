#ifndef LOGICGAMEENGINE_LEVEL_H
#define LOGICGAMEENGINE_LEVEL_H

#include <string>
#include <vector>

class Level {
public:
    using test_T = std::pair<std::vector<bool>, std::vector<bool>>;

    Level() = default;

    void setTitle(const std::wstring &title) {
        m_title = title;
    }

    void setDescription(const std::wstring &description) {
        m_description = description;
    }

    void appendInput(const std::wstring &input) {
        m_inputs.push_back(input);
    }

    void appendOutput(const std::wstring &output) {
        m_outputs.push_back(output);
    }

    void appendAllowedComponent(const std::string &name) {
        m_allowed_components.push_back(name);
    }

    void setVisibleTestsCount(int visible_tests_count) {
        m_visible_tests_count = visible_tests_count;
    }

    void appendTest(const test_T &test) {
        if (test.first.size() != getInputsCount() || test.second.size() != getOutputsCount())
            throw std::runtime_error("Wrong test size");

        m_tests.push_back(test);
    }

    void setPassed(bool is_passed) {
        m_is_passed = is_passed;
    }


    [[nodiscard]] const std::wstring &getTitle() const {
        return m_title;
    }

    [[nodiscard]] const std::wstring &getDescription() const {
        return m_description;
    }

    [[nodiscard]] size_t getInputsCount() const {
        return m_inputs.size();
    }

    [[nodiscard]] size_t getOutputsCount() const {
        return m_outputs.size();
    }

    [[nodiscard]] const std::vector<std::wstring> &getInputs() const {
        return m_inputs;
    }

    [[nodiscard]] const std::vector<std::wstring> &getOutputs() const {
        return m_outputs;
    }

    [[nodiscard]] const std::vector<std::string> &getAllowedComponents() const {
        return m_allowed_components;
    }

    [[nodiscard]] size_t getVisibleTestsCount() const {
        return m_visible_tests_count;
    }

    [[nodiscard]] const std::vector<test_T> &getTests() const {
        return m_tests;
    }

    [[nodiscard]] bool isPassed() const {
        return m_is_passed;
    }

protected:
    std::wstring m_title;
    std::wstring m_description;

    std::vector<std::wstring> m_inputs;
    std::vector<std::wstring> m_outputs;

    std::vector<std::string> m_allowed_components;

    bool m_is_passed{false};

    int m_visible_tests_count{0};
    std::vector<test_T> m_tests;
};

#endif //LOGICGAMEENGINE_LEVEL_H
