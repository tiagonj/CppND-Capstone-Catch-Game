#ifndef CATCH_GAME_BROCCOLI_FACTORY_H
#define CATCH_GAME_BROCCOLI_FACTORY_H

#include "FallerFactory.h"

#include <memory>

// Specialization which generates Broccoli faller objects
class BroccoliFactory : public FallerFactory
{
  public:
    BroccoliFactory(std::weak_ptr<FallerQueue>& queue);
    ~BroccoliFactory();

  private:
    std::unique_ptr<Faller> CreateFaller(float x, float vy) override;

    BroccoliFactory() = delete;
    BroccoliFactory(BroccoliFactory&) = delete;
    BroccoliFactory(BroccoliFactory&&) = delete;
    BroccoliFactory& operator=(BroccoliFactory&) = delete;
    BroccoliFactory& operator=(BroccoliFactory&&) = delete;
};

#endif
