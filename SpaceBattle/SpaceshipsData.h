#pragma once
#include "SpaceshipTypes.h"
#include <boost/json.hpp>
#include <fstream>
#include <map>
#include <memory>

class SpaceshipsData
{
public:
    SpaceshipsData(std::ifstream &settings_file);

    struct Data
    {
        uint64_t _strength;
        uint64_t _damage;
        double _accuracy;
        double _evasion;
        uint64_t _count;
    };

    Data GetDataByType(SpaceshipTypes::Types type);
    std::string GetNameByType(SpaceshipTypes::Types type) const;

private:
    std::map<SpaceshipTypes::Types, Data> _data_map;

private:
    Data Load(boost::json::value &json);
};
