#ifndef CATCH_GAME_OLIVE_H
#define CATCH_GAME_OLIVE_H

#include "Faller.h"

#include <memory>

class Olive : public Faller
{
  public:
    Olive(float x, float vy);
    ~Olive();

  private:
    Olive() = delete;
    Olive(Olive &) = delete;
    Olive(Olive &&) = delete;
    Olive &operator=(Olive &) = delete;
    Olive &operator=(Olive &&) = delete;

  private:
    static std::shared_ptr<ImageArtifact> _oliveImg;
};

#endif
