#include "SpaceshipsData.h"
#include "Spaceship.h"

SpaceshipsData::SpaceshipsData()
{
    std::ifstream settings_file;
    settings_file.open("settings.json");

    boost::json::value _val = boost::json::parse(settings_file);

    Data data{};
    boost::json::value json;
    std::string name;

    SpaceshipTypes::Types current_type = SpaceshipTypes::Types::AllianceShuttle;

    size_t type_index = 0;

    // Alliance spaceships parser
    for (; type_index != SpaceshipTypes::Types::EmpireShuttle; ++type_index)
    {
        name = GetNameByType(current_type);
        json = _val.as_object()["Alliance"].as_object()[name];

        auto data = Load(json);
        _data_map.insert({current_type, data});

        current_type = static_cast<SpaceshipTypes::Types>(type_index);
    }

    // Empire spaceships parser
    for (; type_index != SpaceshipTypes::Types::Count; ++type_index)
    {
        name = GetNameByType(current_type);
        json = _val.as_object()["Empire"].as_object()[name];

        auto data = Load(json);
        _data_map.insert({current_type, data});

        current_type = static_cast<SpaceshipTypes::Types>(type_index);
    }

    settings_file.close();
}

SpaceshipsData::Data SpaceshipsData::GetDataByType(SpaceshipTypes::Types type)
{
    return _data_map[type];
}

std::string SpaceshipsData::GetNameByType(SpaceshipTypes::Types type) const
{
    switch (type)
    {
    case SpaceshipTypes::Types::AllianceShuttle:
        return "Shuttle";
    case SpaceshipTypes::Types::AllianceTransport:
        return "Transport";
    case SpaceshipTypes::Types::AllianceScout:
        return "Scout";
    case SpaceshipTypes::Types::AllianceFighter:
        return "Fighter";
    case SpaceshipTypes::Types::AllianceBomber:
        return "Bomber";
    case SpaceshipTypes::Types::EmpireShuttle:
        return "Shuttle";
    case SpaceshipTypes::Types::EmpireTransport:
        return "Transport";
    case SpaceshipTypes::Types::EmpireScout:
        return "Scout";
    case SpaceshipTypes::Types::EmpireFighter:
        return "Fighter";
    case SpaceshipTypes::Types::EmpireBomber:
        return "Bomber";

    default:
        return "";
    }
}

SpaceshipsData::Data SpaceshipsData::Load(boost::json::value &json)
{
    uint64_t strength = (uint64_t)json.as_object()["Strength"].as_int64();
    uint64_t damage = (uint64_t)json.as_object()["Damage"].as_int64();
    double accuracy = json.as_object()["Accuracy"].as_double();
    double evasion = json.as_object()["Evasion"].as_double();
    uint64_t count = (uint64_t)json.as_object()["Count"].as_int64();

    return Data{strength, damage, accuracy, evasion, count};
}
