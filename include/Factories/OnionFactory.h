#ifndef CATCH_GAME_ONION_FACTORY_H
#define CATCH_GAME_ONION_FACTORY_H

#include "FallerFactory.h"

#include <memory>

// Specialization which generates Onion faller objects
class OnionFactory : public FallerFactory
{
  public:
    OnionFactory(std::weak_ptr<FallerQueue>& queue);
    ~OnionFactory();

  private:
    std::unique_ptr<Faller> CreateFaller(float x, float vy) override;

    OnionFactory() = delete;
    OnionFactory(OnionFactory&) = delete;
    OnionFactory(OnionFactory&&) = delete;
    OnionFactory& operator=(OnionFactory&) = delete;
    OnionFactory& operator=(OnionFactory&&) = delete;
};

#endif
