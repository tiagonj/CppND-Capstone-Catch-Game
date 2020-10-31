#include "AvocadoFactory.h"
#include "Avocado.h"

#define GENERATION_PROBABILITY ((double)0.10)
#define UPDATE_PERIOD_IN_MS ((uint32_t)2500)
#define MAX_VEL_IN_PERCENT_PER_SEC ((float)0.65f)
#define INITIAL_HORIZONTAL_VELOCITY ((float)0.0f)

AvocadoFactory::AvocadoFactory(std::weak_ptr<FallerQueue>& queue)
    : FallerFactory(GENERATION_PROBABILITY, UPDATE_PERIOD_IN_MS, MAX_VEL_IN_PERCENT_PER_SEC, queue)
{
}

AvocadoFactory::~AvocadoFactory()
{
}

std::unique_ptr<Faller> AvocadoFactory::CreateFaller(float x, float vy)
{
    return std::make_unique<Avocado>(x, INITIAL_HORIZONTAL_VELOCITY, vy);
}
