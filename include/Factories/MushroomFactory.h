#ifndef CATCH_GAME_MUSHROOM_FACTORY_H
#define CATCH_GAME_MUSHROOM_FACTORY_H

#include "FallerFactory.h"

#include <memory>

// Specialization which generates Mushroom faller objects
class MushroomFactory : public FallerFactory
{
  public:
    MushroomFactory(std::weak_ptr<FallerQueue>& queue);
    ~MushroomFactory();

  private:
    std::unique_ptr<Faller> CreateFaller(float x, float vy) override;

    MushroomFactory() = delete;
    MushroomFactory(MushroomFactory&) = delete;
    MushroomFactory(MushroomFactory&&) = delete;
    MushroomFactory& operator=(MushroomFactory&) = delete;
    MushroomFactory& operator=(MushroomFactory&&) = delete;
};

#endif
