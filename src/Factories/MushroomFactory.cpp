#include "MushroomFactory.h"
#include "Mushroom.h"

#define GENERATION_PROBABILITY ((double)0.05)
#define UPDATE_PERIOD_IN_MS ((uint32_t)4000)
#define MAX_VEL_IN_PERCENT_PER_SEC ((float)0.70f)
#define INITIAL_HORIZONTAL_VELOCITY ((float)0.0f)

MushroomFactory::MushroomFactory(std::weak_ptr<FallerQueue>& queue)
    : FallerFactory(GENERATION_PROBABILITY, UPDATE_PERIOD_IN_MS, MAX_VEL_IN_PERCENT_PER_SEC, queue)
{
}

MushroomFactory::~MushroomFactory()
{
}

std::unique_ptr<Faller> MushroomFactory::CreateFaller(float x, float vy)
{
    return std::make_unique<Mushroom>(x, INITIAL_HORIZONTAL_VELOCITY, vy);
}
