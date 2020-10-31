#include "OnionFactory.h"
#include "Onion.h"

#define GENERATION_PROBABILITY ((double)0.25)
#define UPDATE_PERIOD_IN_MS ((uint32_t)1500)
#define MAX_VEL_IN_PERCENT_PER_SEC ((float)0.55f)
#define INITIAL_HORIZONTAL_VELOCITY ((float)0.0f)

OnionFactory::OnionFactory(std::weak_ptr<FallerQueue>& queue)
    : FallerFactory(GENERATION_PROBABILITY, UPDATE_PERIOD_IN_MS, MAX_VEL_IN_PERCENT_PER_SEC, queue)
{
}

OnionFactory::~OnionFactory()
{
}

std::unique_ptr<Faller> OnionFactory::CreateFaller(float x, float vy)
{
    return std::make_unique<Onion>(x, INITIAL_HORIZONTAL_VELOCITY, vy);
}
