#ifndef LOGICGAMEENGINE_FONTMANAGER_H
#define LOGICGAMEENGINE_FONTMANAGER_H

#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class FontManager : public ResourceManager<FontManager, sf::Font> {
public:
    FontManager() : ResourceManager("fonts.cfg") {}

    sf::Font *Load(const std::string &path) {
        auto *font = new sf::Font();
        if (!font->loadFromFile(path)) {
            delete font;
            font = nullptr;
            std::cerr << "! Failed to load font: "
                      << path << std::endl;
        }
        return font;
    }
};

#endif //LOGICGAMEENGINE_FONTMANAGER_H
