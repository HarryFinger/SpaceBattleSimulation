#pragma once
#include <boost/json.hpp>
#include <fstream>
#include <map>
#include <memory>


class SpaceshipsData
{
public:
    SpaceshipsData();

    enum SpaceshipID
    {
        AllianceShuttle,
        AllianceTransport,
        AllianceScout,
        AllianceFighter,
        AllianceBomber,

        EmpireShuttle,
        EmpireTransport,
        EmpireScout,
        EmpireFighter,
        EmpireBomber,

        Count
    };

    struct Data
    {
        uint64_t _strength;
        uint64_t _damage;
        double _accuracy;
        double _evasion;
        uint64_t _count;
    };

    Data GetDataByType(SpaceshipID spaceship_id);
    std::string GetNameByType(SpaceshipID spaceship_id) const;

private:
    std::map<SpaceshipID, Data> _data_map;

private:

    Data Load(boost::json::value &json);
};
