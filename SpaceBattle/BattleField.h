#pragma once
#include "Spaceship.h"
#include <fstream>
#include <memory>
#include <vector>

class SpaceshipsData;

class BattleField
{
public:
    BattleField(SpaceshipsData *spaceships_data);
    void SimulateBattle();

private:
    using Spaceships = std::vector<std::unique_ptr<Spaceship>>;

    // set in BattleField constructor for each fraction
    struct ArmyStruture
    {
        size_t shuttle_count;
        size_t transport_count;
        size_t scout_count;
        size_t fighter_count;
        size_t bomber_count;
    };

    void CreateArmy(Spaceship::Fraction fraction_type, const ArmyStruture &army_structure);
    uint64_t CalculateDamage(const Spaceship *shooter, const Spaceship *target) const;
    void LogTurnResult(std::ostream *stream, const Spaceship *shooter, const Spaceship *target, uint64_t damage) const;
    void LogResultInfo(std::ostream *stream, const Spaceships *current_army) const;

private:
    SpaceshipsData *_spaceships_data;
    std::unique_ptr<std::ostream> _output;
    Spaceships _alliance_army;
    Spaceships _empire_army;
};
