#pragma once
#include "Spaceship.h"
#include <memory>

class SpaceshipFactory
{
public:
    virtual std::unique_ptr<Spaceship> CreateSpaceship(Spaceship::SpaceshipType spaceship_type, uint64_t strength,
                                                        uint64_t damage, double accuracy, double evasion,
                                                        const std::string &name) = 0;
};
