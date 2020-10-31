#ifndef CATCH_GAME_MUSHROOM_H
#define CATCH_GAME_MUSHROOM_H

#include "Faller.h"

#include <string>

class Mushroom : public Faller
{
  public:
    Mushroom(float x, float vx, float vy);
    ~Mushroom();
    std::string& Name() const override;

  private:
    Mushroom() = delete;
    Mushroom(Mushroom&) = delete;
    Mushroom(Mushroom&&) = delete;
    Mushroom& operator=(Mushroom&) = delete;
    Mushroom& operator=(Mushroom&&) = delete;

  private:
    static std::string _name;
};

#endif
