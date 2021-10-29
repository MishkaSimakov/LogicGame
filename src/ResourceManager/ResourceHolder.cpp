#include "ResourceHolder.h"

ResourceHolder::ResourceHolder() :
    fonts("fonts", "ttf"),
    textures("txrs", "png")
{}

ResourceHolder &ResourceHolder::get()
{
    static ResourceHolder holder;

    return holder;
}
