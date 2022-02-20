#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "ResourceManager.h"
#include "SmoothTexture.h"

class ResourceHolder {
public:
    static ResourceHolder &get();

    ResourceManager<sf::Font> fonts;
    ResourceManager<SmoothTexture> textures;
private:
    ResourceHolder();
};

#endif // RESOURCEHOLDER_H
