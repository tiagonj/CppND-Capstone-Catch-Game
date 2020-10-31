#ifndef CATCH_GAME_ONION_H
#define CATCH_GAME_ONION_H

#include "Faller.h"

#include <string>

class Onion : public Faller
{
  public:
    Onion(float x, float vx, float vy);
    ~Onion();
    std::string& Name() const override;

  private:
    Onion() = delete;
    Onion(Onion&) = delete;
    Onion(Onion&&) = delete;
    Onion& operator=(Onion&) = delete;
    Onion& operator=(Onion&&) = delete;

  private:
    static std::string _name;
};

#endif
