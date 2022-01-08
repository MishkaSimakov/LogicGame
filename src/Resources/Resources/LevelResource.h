#ifndef LOGICGAMEENGINE_LEVELRESOURCE_H
#define LOGICGAMEENGINE_LEVELRESOURCE_H

#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Resources {
    class LevelResource {
    public:
        using test_T = std::pair<std::vector<bool>, std::vector<bool>>;

        LevelResource() = default;

        // TODO: add memory cleaning after end

        [[nodiscard]] const std::wstring &getTitle() const {
            return m_title;
        }

        [[nodiscard]] const std::wstring &getDescription() const {
            return m_description;
        }

        bool loadFromFile(const std::string &filename) {
            std::wifstream file;
            file.open(filename);

            if (!file.is_open())
                return false;

            readTitle(file);
            readDescription(file);
            readInputsOutputsCount(file);
            readTests(file);

            file.close();

            return true;
        }

        [[nodiscard]] int getInputsCount() const {
            return m_inputs_count;
        }

        [[nodiscard]] int getOutputsCount() const {
            return m_outputs_count;
        }

        [[nodiscard]] const std::vector<test_T> &getTests() const {
            return m_tests;
        }

    protected:
        void readTitle(std::wifstream &file) {
            std::getline(file, m_title);
            m_title = sf::String::fromUtf8(m_title.begin(), m_title.end());
        }

        void readDescription(std::wifstream &file) {
            std::wstring temp;
            std::getline(file, temp);

            while (temp != m_end_description_code) {
                m_description += temp + L'\n';

                std::getline(file, temp);
            }

            m_description = sf::String::fromUtf8(m_description.begin(), m_description.end());
        }

        void readInputsOutputsCount(std::wifstream &file) {
            std::wstring temp;

            std::getline(file, temp, L' ');
            m_inputs_count = std::stoi(temp);

            std::getline(file, temp, L'\n');
            m_outputs_count = std::stoi(temp);
        }

        void readTests(std::wifstream &file) {
            std::wstring temp;

            while (file.peek() != EOF) {
                std::getline(file, temp);

                test_T test;

                int i = 0;
                for (wchar_t c: temp) {
                    if (c != L' ') {
                        if (i < m_inputs_count)
                            test.first.push_back(c == L'1');
                        else
                            test.second.push_back(c == L'1');

                        ++i;
                    }
                }

                m_tests.push_back(std::move(test));
            }
        }

        const std::wstring m_end_description_code{L"#description_end"};

        std::wstring m_title;
        std::wstring m_description;
        int m_inputs_count{0};
        int m_outputs_count{0};

        std::vector<test_T> m_tests;
    };
}


#endif //LOGICGAMEENGINE_LEVELRESOURCE_H
