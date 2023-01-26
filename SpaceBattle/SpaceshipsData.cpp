#include "SpaceshipsData.h"

SpaceshipsData::SpaceshipsData()
{
    std::ifstream settings_file;
    settings_file.open("settings.json");

    boost::json::value _val = boost::json::parse(settings_file);

    Data data{};
    boost::json::value json;
    std::string name;

    SpaceshipID current_type = SpaceshipID::AllianceShuttle;

    size_t type_index = 0;

    // Alliance spaceships parser
    for (; type_index != SpaceshipID::EmpireShuttle; ++type_index)
    {
        name = GetNameByType(current_type);
        json = _val.as_object()["Alliance"].as_object()[name];

        auto data = Load(json);
        _data_map.insert({current_type, data});

        current_type = static_cast<SpaceshipID>(type_index);
    }

    // Empire spaceships parser
    for (; type_index != SpaceshipID::Count; ++type_index)
    {
        name = GetNameByType(current_type);
        json = _val.as_object()["Empire"].as_object()[name];

        auto data = Load(json);
        _data_map.insert({current_type, data});

        current_type = static_cast<SpaceshipID>(type_index);
    }

    settings_file.close();
}

SpaceshipsData::Data SpaceshipsData::GetDataByType(SpaceshipID spaceship_id)
{
    return _data_map[spaceship_id];
}

std::string SpaceshipsData::GetNameByType(SpaceshipID spaceship_id) const
{
    switch (spaceship_id)
    {
    case SpaceshipID::AllianceShuttle:
        return "Shuttle";
    case SpaceshipID::AllianceTransport:
        return "Transport";
    case SpaceshipID::AllianceScout:
        return "Scout";
    case SpaceshipID::AllianceFighter:
        return "Fighter";
    case SpaceshipID::AllianceBomber:
        return "Bomber";
    case SpaceshipID::EmpireShuttle:
        return "Shuttle";
    case SpaceshipID::EmpireTransport:
        return "Transport";
    case SpaceshipID::EmpireScout:
        return "Scout";
    case SpaceshipID::EmpireFighter:
        return "Fighter";
    case SpaceshipID::EmpireBomber:
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
