#include "EmpireFactory.h"
#include "Bomber.h"
#include "Fighter.h"
#include "Scout.h"
#include "Shuttle.h"
#include "SpaceshipsData.h"
#include "Transport.h"

namespace
{
const std::string fraction_posfix = "-E";
}

EmpireFactory::EmpireFactory(SpaceshipsData *spaceships_data) : SpaceshipFactory(spaceships_data)
{
}

std::unique_ptr<Spaceship> EmpireFactory::CreateShuttle(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::EmpireShuttle;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Shuttle>(Spaceship::Fraction::Empire, val._strength, val._damage, val._accuracy,
                                     val._evasion, name);
}

std::unique_ptr<Spaceship> EmpireFactory::CreateTransport(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::EmpireTransport;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Transport>(Spaceship::Fraction::Empire, val._strength, val._damage, val._accuracy,
                                     val._evasion, name);
}

std::unique_ptr<Spaceship> EmpireFactory::CreateScout(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::EmpireScout;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Scout>(Spaceship::Fraction::Empire, val._strength, val._damage, val._accuracy,
                                       val._evasion, name);
}

std::unique_ptr<Spaceship> EmpireFactory::CreateFighter(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::EmpireFighter;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Fighter>(Spaceship::Fraction::Empire, val._strength, val._damage, val._accuracy, val._evasion,
                                   name);
}

std::unique_ptr<Spaceship> EmpireFactory::CreateBomber(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::EmpireBomber;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Bomber>(Spaceship::Fraction::Empire, val._strength, val._damage, val._accuracy,
                                     val._evasion, name);
}