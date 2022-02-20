#include "ResourceHolder.h"

ResourceHolder::ResourceHolder() :
        fonts("fonts", "ttf"),
        textures("textures", "png") {}

ResourceHolder &ResourceHolder::get() {
    static ResourceHolder holder;

    return holder;
}
