#pragma once
#include "Spaceship.h"

class Bomber : public Spaceship
{
public:
    Bomber(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
           const std::string &name);
    SpaceshipType GetType() const override;
};
