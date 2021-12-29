#ifndef LOGICGAMEENGINE_LEVELRESOURCE_H
#define LOGICGAMEENGINE_LEVELRESOURCE_H

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

namespace Resources {
    class LevelResource {
    public:
        LevelResource() = default;

        const std::wstring &getTitle() const {
            return title;
        }

        const std::wstring &getDescription() const {
            return description;
        }

        bool loadFromFile(const std::string& filename) {
            std::wifstream file;
            file.open(filename);

            if (!file.is_open())
                return false;

            std::getline(file, title);
            std::getline(file, description);

            file.close();

            title = sf::String::fromUtf8(title.begin(), title.end());
            description = sf::String::fromUtf8(description.begin(), description.end());

            return true;
        }

    protected:
        std::wstring title;
        std::wstring description;
    };
}


#endif //LOGICGAMEENGINE_LEVELRESOURCE_H
