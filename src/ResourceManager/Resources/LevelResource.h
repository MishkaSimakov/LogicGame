#ifndef LOGICGAMEENGINE_LEVELRESOURCE_H
#define LOGICGAMEENGINE_LEVELRESOURCE_H

#include <string>
#include <fstream>

namespace Resources {
    class LevelResource {
    public:
        LevelResource() = default;

        const std::string &getTitle() const {
            return title;
        }

        const std::string &getDescription() const {
            return description;
        }

        bool loadFromFile(const std::string& filename) {
            std::ifstream file;
            file.open(filename);

            if (!file.is_open())
                return false;

            std::getline(file, title);
            std::getline(file, description);

            file.close();

            return true;
        }

    protected:
        std::string title;
        std::string description;
    };
}


#endif //LOGICGAMEENGINE_LEVELRESOURCE_H
