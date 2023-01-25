#pragma once
#include "Spaceship.h"

class Transport : public Spaceship
{
public:
    Transport(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
              const std::string &name);
    SpaceshipType GetType() const override;
};
