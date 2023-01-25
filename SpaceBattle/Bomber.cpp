#include "Bomber.h"

Bomber::Bomber(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
               const std::string &name)
    : Spaceship(fraction, strength, damage, accuracy, evasion, name)
{
}

Bomber::SpaceshipType Bomber::GetType() const
{
    return SpaceshipType::Bomber;
}
