#pragma once
#include "SpaceshipFactory.h"

class SpaceshipsData;

class AllianceFactory final : public SpaceshipFactory
{
public:
    AllianceFactory(SpaceshipsData *spaceships_data);

    std::unique_ptr<Spaceship> CreateShuttle(size_t fraction_id) override;
    std::unique_ptr<Spaceship> CreateTransport(size_t fraction_id) override;
    std::unique_ptr<Spaceship> CreateScout(size_t fraction_id) override;
    std::unique_ptr<Spaceship> CreateFighter(size_t fraction_id) override;
    std::unique_ptr<Spaceship> CreateBomber(size_t fraction_id) override;
};
