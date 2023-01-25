#pragma once
#include "SpaceshipFactory.h"


class EmpireFactory : public SpaceshipFactory
{
public:
    std::unique_ptr<Spaceship> CreateSpaceship(Spaceship::SpaceshipType spaceship_type, uint64_t strength, uint64_t damage, double accuracy, double evasion,
                                                const std::string &name) override;
};
