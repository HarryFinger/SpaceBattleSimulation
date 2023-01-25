#pragma once
#include "SpaceshipFactory.h"
#include <boost/json.hpp>
#include <fstream>
#include <memory>
#include <vector>

class BattleField
{
public:
    BattleField(std::ifstream &settings_file);
    void SimulateBattle();

private:
    void ReleaseArmy(Spaceship::Fraction fraction_type);
    using Spaceships = std::vector<std::unique_ptr<Spaceship>>;
    void LogTurnResult(std::ostream &stream, Spaceships *current_army, Spaceships *target_army, size_t current_ship,
                       size_t target_ship, uint64_t damage);
    void LogResultInfo(std::ostream &stream, Spaceships *current_army);

    struct Data
    {
        void Load(boost::json::value &json);

        uint64_t strength;
        uint64_t damage;
        double accuracy;
        double evasion;
        uint64_t count;
    };

private:
    std::ofstream output;
    boost::json::value _val;
    Spaceships _alliance_army;
    Spaceships _empire_army;
};
