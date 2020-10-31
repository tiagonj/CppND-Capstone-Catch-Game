#include "Avocado.h"

#include <cassert>

#define AVOCADO_SPRITE_HEIGHT ((float)0.07401316f) // Maintain original sprite h/w ratio
#define AVOCADO_SPRITE_WIDTH ((float)0.05f)
#define AVOCADO_REWARD_POINTS ((uint32_t)10)

std::string Avocado::_name{"avocado"};

Avocado::Avocado(float x, float vx, float vy)
    : Faller(AVOCADO_SPRITE_WIDTH, AVOCADO_SPRITE_HEIGHT, x, vx, vy, AVOCADO_REWARD_POINTS)
{
}

Avocado::~Avocado()
{
}

std::string& Avocado::Name() const
{
    return _name;
}
