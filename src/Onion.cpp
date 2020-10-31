#include "Onion.h"

#include <cassert>

#define ONION_SPRITE_HEIGHT ((float)0.05686f) // Maintain original sprite h/w ratio
#define ONION_SPRITE_WIDTH ((float)0.05f)
#define ONION_REWARD_POINTS ((uint32_t)2)

std::string Onion::_name{"onion"};

Onion::Onion(float x, float vx, float vy)
    : Faller(ONION_SPRITE_WIDTH, ONION_SPRITE_HEIGHT, x, vx, vy, ONION_REWARD_POINTS)
{
}

Onion::~Onion()
{
}

std::string& Onion::Name() const
{
    return _name;
}
