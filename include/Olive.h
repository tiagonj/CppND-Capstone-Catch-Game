#ifndef CATCH_GAME_OLIVE_H
#define CATCH_GAME_OLIVE_H

#include "Faller.h"

#include <string>

class Olive : public Faller
{
  public:
    Olive(float x, float vx, float vy);
    ~Olive();
    std::string& Name() const override;

  private:
    Olive() = delete;
    Olive(Olive&) = delete;
    Olive(Olive&&) = delete;
    Olive& operator=(Olive&) = delete;
    Olive& operator=(Olive&&) = delete;

  private:
    static std::string _name;
};

#endif
