#include "OliveFactory.h"
#include "Olive.h"

#define GENERATION_PROBABILITY ((double)0.2)
#define UPDATE_PERIOD_IN_MS ((uint32_t)650)
#define MAX_VEL_IN_PERCENT_PER_SEC ((float)0.5f)

OliveFactory::OliveFactory(std::weak_ptr<FallerQueue>& queue)
    : FallerFactory(GENERATION_PROBABILITY, UPDATE_PERIOD_IN_MS, MAX_VEL_IN_PERCENT_PER_SEC, queue)
{
}

OliveFactory::~OliveFactory()
{
}

std::unique_ptr<Faller> OliveFactory::CreateFaller(float x, float vy)
{
    return std::make_unique<Olive>(x, vy);
}
