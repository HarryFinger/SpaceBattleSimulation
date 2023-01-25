#include "Transport.h"

Transport::Transport(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
                     const std::string &name)
    : Spaceship(fraction, strength, damage, accuracy, evasion, name)
{
}

Transport::SpaceshipType Transport::GetType() const
{
    return SpaceshipType::Transport;
}