#include "BroccoliFactory.h"
#include "Broccoli.h"

#define GENERATION_PROBABILITY ((double)0.15)
#define UPDATE_PERIOD_IN_MS ((uint32_t)2000)
#define MAX_VEL_IN_PERCENT_PER_SEC ((float)0.6f)
#define INITIAL_HORIZONTAL_VELOCITY ((float)0.0f)

BroccoliFactory::BroccoliFactory(std::weak_ptr<FallerQueue>& queue)
    : FallerFactory(GENERATION_PROBABILITY, UPDATE_PERIOD_IN_MS, MAX_VEL_IN_PERCENT_PER_SEC, queue)
{
}

BroccoliFactory::~BroccoliFactory()
{
}

std::unique_ptr<Faller> BroccoliFactory::CreateFaller(float x, float vy)
{
    return std::make_unique<Broccoli>(x, INITIAL_HORIZONTAL_VELOCITY, vy);
}
