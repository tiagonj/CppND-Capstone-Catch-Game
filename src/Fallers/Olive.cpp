#include "Olive.h"

#include <cassert>

#define OLIVE_SPRITE_HEIGHT ((float)0.05f)
#define OLIVE_SPRITE_WIDTH ((float)0.05f)
#define OLIVE_REWARD_POINTS ((uint32_t)1)

std::string Olive::_name{"olive"};

Olive::Olive(float x, float vx, float vy)
    : Faller(OLIVE_SPRITE_WIDTH, OLIVE_SPRITE_HEIGHT, x, vx, vy, OLIVE_REWARD_POINTS)
{
}

Olive::~Olive()
{
}

std::string& Olive::Name() const
{
    return _name;
}
