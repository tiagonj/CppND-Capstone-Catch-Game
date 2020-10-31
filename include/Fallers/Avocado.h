#ifndef CATCH_GAME_AVOCADO_H
#define CATCH_GAME_AVOCADO_H

#include "Faller.h"

#include <string>

class Avocado : public Faller
{
  public:
    Avocado(float x, float vx, float vy);
    ~Avocado();
    std::string& Name() const override;

  private:
    Avocado() = delete;
    Avocado(Avocado&) = delete;
    Avocado(Avocado&&) = delete;
    Avocado& operator=(Avocado&) = delete;
    Avocado& operator=(Avocado&&) = delete;

  private:
    static std::string _name;
};

#endif
