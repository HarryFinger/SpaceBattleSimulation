#include "Fighter.h"

Fighter::Fighter(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
                 const std::string &name)
    : Spaceship(fraction, strength, damage, accuracy, evasion, name)
{
}

Fighter::SpaceshipType Fighter::GetType() const
{
    return SpaceshipType::Fighter;
}