#include "Shuttle.h"

Shuttle::Shuttle(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
                 const std::string &name)
    : Spaceship(fraction, strength, damage, accuracy, evasion, name)
{
}

Shuttle::SpaceshipType Shuttle::GetType() const
{
    return SpaceshipType::Shuttle;
}