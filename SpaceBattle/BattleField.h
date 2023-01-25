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
    using Spaceships = std::vector<std::unique_ptr<Spaceship>>;

    struct Data
    {
        void Load(boost::json::value &json);

        uint64_t strength;
        uint64_t damage;
        double accuracy;
        double evasion;
        uint64_t count;
    };

    void CreateArmy(Spaceship::Fraction fraction_type);
    uint64_t CalculateDamage(const Spaceship *shooter, const Spaceship *target) const;
    void LogTurnResult(std::ostream &stream, const Spaceship *shooter, const Spaceship *target, uint64_t damage) const;
    void LogResultInfo(std::ostream &stream, const Spaceships *current_army) const;

private:
    std::ofstream output;
    boost::json::value _val;
    Spaceships _alliance_army;
    Spaceships _empire_army;
};
