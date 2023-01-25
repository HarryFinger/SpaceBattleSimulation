#include "Scout.h"

Scout::Scout(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
             const std::string &name)
    : Spaceship(fraction, strength, damage, accuracy, evasion, name)
{
}

Scout::SpaceshipType Scout::GetType() const
{
    return SpaceshipType::Scout;
}