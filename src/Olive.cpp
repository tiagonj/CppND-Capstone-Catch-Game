#include "Olive.h"

#include <cassert>

#define OLIVE_REWARD_POINTS ((uint32_t)1)
#define OLIVE_HORIZONTAL_VELOCITY ((float)0.0f)

std::shared_ptr<ImageArtifact> Olive::_oliveImg = std::make_shared<ImageArtifact>("olive.ext");

Olive::Olive(float x, float vy)
    : Faller(_oliveImg, x, OLIVE_HORIZONTAL_VELOCITY, vy, OLIVE_REWARD_POINTS)
{
}

Olive::~Olive()
{
}
