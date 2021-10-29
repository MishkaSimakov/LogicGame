#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "ResourceManager.h"
#include "SFML/Graphics.hpp"

class ResourceHolder
{
public:
    static ResourceHolder &get();

    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::Texture> textures;
private:
    ResourceHolder();
};

#endif // RESOURCEHOLDER_H
