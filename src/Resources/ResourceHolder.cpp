#include "ResourceHolder.h"

ResourceHolder::ResourceHolder() :
    fonts("fonts", "ttf"),
    textures("textures", "png"),
    levels("levels", "txt")
{}

ResourceHolder &ResourceHolder::get()
{
    static ResourceHolder holder;

    return holder;
}
