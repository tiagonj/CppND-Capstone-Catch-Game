#include "Mushroom.h"

#include <cassert>

#define MUSHROOM_SPRITE_HEIGHT ((float)0.0454646f) // Maintain original sprite h/w ratio
#define MUSHROOM_SPRITE_WIDTH ((float)0.05f)
#define MUSHROOM_REWARD_POINTS ((uint32_t)25)

std::string Mushroom::_name{"mushroom"};

Mushroom::Mushroom(float x, float vx, float vy)
    : Faller(MUSHROOM_SPRITE_WIDTH, MUSHROOM_SPRITE_HEIGHT, x, vx, vy, MUSHROOM_REWARD_POINTS)
{
}

Mushroom::~Mushroom()
{
}

std::string& Mushroom::Name() const
{
    return _name;
}
