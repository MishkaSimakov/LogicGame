#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include "LevelResource.h"

class ResourceHolder
{
public:
    static ResourceHolder &get();

    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::Texture> textures;
    ResourceManager<Resources::LevelResource> levels;
private:
    ResourceHolder();
};

#endif // RESOURCEHOLDER_H
