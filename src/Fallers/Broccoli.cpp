#include "Broccoli.h"

#include <cassert>

#define BROCCOLI_SPRITE_HEIGHT ((float)0.0572152f) // Maintain original sprite h/w ratio
#define BROCCOLI_SPRITE_WIDTH ((float)0.05f)
#define BROCCOLI_REWARD_POINTS ((uint32_t)5)

std::string Broccoli::_name{"broccoli"};

Broccoli::Broccoli(float x, float vx, float vy)
    : Faller(BROCCOLI_SPRITE_WIDTH, BROCCOLI_SPRITE_HEIGHT, x, vx, vy, BROCCOLI_REWARD_POINTS)
{
}

Broccoli::~Broccoli()
{
}

std::string& Broccoli::Name() const
{
    return _name;
}
