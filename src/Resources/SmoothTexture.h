#ifndef LOGICGAMEENGINE_SMOOTHTEXTURE_H
#define LOGICGAMEENGINE_SMOOTHTEXTURE_H

#include <SFML/Graphics.hpp>

class SmoothTexture : public sf::Texture {
    using sf::Texture::Texture;

public:
    bool loadFromFile(const std::string &filename, const sf::IntRect &area = sf::IntRect()) {
        setSmooth(true);

        return sf::Texture::loadFromFile(filename, area);
    }
};

#endif //LOGICGAMEENGINE_SMOOTHTEXTURE_H
