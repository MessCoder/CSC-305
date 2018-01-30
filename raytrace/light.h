#ifndef LIGHT_H
#define LIGHT_H

#include "common.h"

class Light
{
public:
    Vec3 pos;
    float intensity;

    Light(Vec3 pos, float intensity);
};

#endif // LIGHT_H
