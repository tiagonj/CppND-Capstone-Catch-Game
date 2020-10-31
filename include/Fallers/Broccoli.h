#ifndef CATCH_GAME_BROCCOLI_H
#define CATCH_GAME_BROCCOLI_H

#include "Faller.h"

#include <string>

class Broccoli : public Faller
{
  public:
    Broccoli(float x, float vx, float vy);
    ~Broccoli();
    std::string& Name() const override;

  private:
    Broccoli() = delete;
    Broccoli(Broccoli&) = delete;
    Broccoli(Broccoli&&) = delete;
    Broccoli& operator=(Broccoli&) = delete;
    Broccoli& operator=(Broccoli&&) = delete;

  private:
    static std::string _name;
};

#endif
