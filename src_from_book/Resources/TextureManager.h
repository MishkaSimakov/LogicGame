#ifndef LOGICGAMEENGINE_TEXTUREMANAGER_H
#define LOGICGAMEENGINE_TEXTUREMANAGER_H

#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <string>

class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
public:
    TextureManager() : ResourceManager("textures.cfg") {}

    sf::Texture *Load(const std::string &path) {
        auto *texture = new sf::Texture();
        if (!texture->loadFromFile(path)) {
            delete texture;
            texture = nullptr;
            std::cerr << "! Failed to load texture: "
                      << path << std::endl;
        }
        return texture;
    }
};

#endif //LOGICGAMEENGINE_TEXTUREMANAGER_H
