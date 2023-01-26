#include "AllianceFactory.h"
#include "Bomber.h"
#include "Fighter.h"
#include "Scout.h"
#include "Shuttle.h"
#include "SpaceshipsData.h"
#include "Transport.h"

namespace
{
const std::string fraction_posfix = "-A";
}


AllianceFactory::AllianceFactory(SpaceshipsData *spaceships_data) : SpaceshipFactory(spaceships_data)
{
}

std::unique_ptr<Spaceship> AllianceFactory::CreateShuttle(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::AllianceShuttle;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Shuttle>(Spaceship::Fraction::Alliance, val._strength, val._damage, val._accuracy,
                                     val._evasion, name);
}

std::unique_ptr<Spaceship> AllianceFactory::CreateTransport(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::AllianceTransport;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Transport>(Spaceship::Fraction::Alliance, val._strength, val._damage, val._accuracy,
                                     val._evasion, name);
}

std::unique_ptr<Spaceship> AllianceFactory::CreateScout(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::AllianceScout;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Scout>(Spaceship::Fraction::Alliance, val._strength, val._damage, val._accuracy,
                                       val._evasion, name);
}

std::unique_ptr<Spaceship> AllianceFactory::CreateFighter(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::AllianceFighter;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Fighter>(Spaceship::Fraction::Alliance, val._strength, val._damage, val._accuracy,
                                   val._evasion, name);
}

std::unique_ptr<Spaceship> AllianceFactory::CreateBomber(size_t fraction_id)
{
    SpaceshipTypes::Types type = SpaceshipTypes::Types::AllianceBomber;
    auto val = _spaceships_data->GetDataByType(type);
    std::string name = _spaceships_data->GetNameByType(type) + fraction_posfix + std::to_string(fraction_id);

    return std::make_unique<Bomber>(Spaceship::Fraction::Alliance, val._strength, val._damage, val._accuracy,
                                     val._evasion, name);
}
