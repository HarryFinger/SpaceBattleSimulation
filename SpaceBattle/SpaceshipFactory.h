#pragma once
#include "Spaceship.h"
#include "SpaceshipTypes.h"
#include <memory>

class SpaceshipsData;

class SpaceshipFactory
{
public:
    SpaceshipFactory() = default;

    SpaceshipFactory(SpaceshipsData *spaceships_data) : _spaceships_data(spaceships_data)
    {
    }

    virtual std::unique_ptr<Spaceship> CreateShuttle(size_t fraction_id) = 0;
    virtual std::unique_ptr<Spaceship> CreateTransport(size_t fraction_id) = 0;
    virtual std::unique_ptr<Spaceship> CreateScout(size_t fraction_id) = 0;
    virtual std::unique_ptr<Spaceship> CreateFighter(size_t fraction_id) = 0;
    virtual std::unique_ptr<Spaceship> CreateBomber(size_t fraction_id) = 0;

protected:
    SpaceshipsData *_spaceships_data;
};
