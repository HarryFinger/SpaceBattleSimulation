#include "BattleField.h"
#include "AllianceFactory.h"
#include "EmpireFactory.h"
#include "RandomTool.h"
#include <iostream>
#include <random>

BattleField::BattleField(SpaceshipsData *spaceships_data) : _spaceships_data(spaceships_data)
{
    _output.open("output.txt");

    // task was ambiguous
    // on the one hand, the task indicated "the amount to install independently",
    // on the other hand, "read from JSON"
    // in any case, it was decided to leave count field in SpaceshipsData
    ArmyStruture alliance_army_structure{2, 2, 1, 2, 1};
    CreateArmy(Spaceship::Fraction::Alliance, alliance_army_structure);

    ArmyStruture empire_army_structure{1, 2, 2, 1, 1};
    CreateArmy(Spaceship::Fraction::Empire, empire_army_structure);
}

void BattleField::CreateArmy(Spaceship::Fraction fraction, const ArmyStruture &army_structure)
{
    std::unique_ptr<SpaceshipFactory> factory;
    Spaceships *spaceships = nullptr;

    size_t fraction_id = 1;

    switch (fraction)
    {
    case Spaceship::Fraction::Alliance:
        factory = std::make_unique<AllianceFactory>(_spaceships_data);
        spaceships = &_alliance_army;
        break;
    case Spaceship::Fraction::Empire:
        factory = std::make_unique<EmpireFactory>(_spaceships_data);
        spaceships = &_empire_army;
        break;
    }

    for (size_t i = 0; i < army_structure.shuttle_count; i++)
    {
        spaceships->push_back(factory->CreateShuttle(fraction_id));
        ++fraction_id;
    }

    for (size_t i = 0; i < army_structure.transport_count; i++)
    {
        spaceships->push_back(factory->CreateTransport(fraction_id));
        ++fraction_id;
    }

    for (size_t i = 0; i < army_structure.scout_count; i++)
    {
        spaceships->push_back(factory->CreateScout(fraction_id));
        ++fraction_id;
    }

    for (size_t i = 0; i < army_structure.fighter_count; i++)
    {
        spaceships->push_back(factory->CreateFighter(fraction_id));
        ++fraction_id;
    }

    for (size_t i = 0; i < army_structure.bomber_count; i++)
    {
        spaceships->push_back(factory->CreateBomber(fraction_id));
        ++fraction_id;
    }
}

void BattleField::SimulateBattle()
{
    Spaceships *current_army = nullptr;
    Spaceships *target_army = nullptr;

    enum class FractionTurn
    {
        AllianceTurn,
        EmpireTurn
    };

    // shuffling first turn
    FractionTurn frac_turn = random_tool::RandomValueInRange(2) ? FractionTurn::AllianceTurn : FractionTurn::EmpireTurn;

    // battle begins
    while (_alliance_army.size() > 0 and _empire_army.size() > 0)
    {
        switch (frac_turn)
        {
        case FractionTurn::AllianceTurn:
            current_army = &_alliance_army;
            target_army = &_empire_army;

            // NEXT turn will be Empire Turn
            frac_turn = FractionTurn::EmpireTurn;
            break;
        case FractionTurn::EmpireTurn:
            current_army = &_empire_army;
            target_army = &_alliance_army;

            // NEXT turn will be Alliance Turn
            frac_turn = FractionTurn::AllianceTurn;
            break;
        }

        size_t current_army_size = current_army->size();
        size_t target_army_size = target_army->size();

        size_t current_ship_index = random_tool::RandomValueInRange((uint32_t)current_army_size);
        size_t target_ship_index = random_tool::RandomValueInRange((uint32_t)target_army_size);

        Spaceship *shooter = (*current_army)[current_ship_index].get();
        Spaceship *target = (*target_army)[target_ship_index].get();

        uint64_t damage = CalculateDamage(shooter, target);
        target->ApplyDamage(damage);

        // turn result info
        LogTurnResult(_output, shooter, target, damage);

        // destroy target army spaceship if strength is less or equal to 0
        if (target->GetStrength() == 0)
        {
            std::swap((*target_army)[target_ship_index], (*target_army)[target_army_size - 1]);
            target_army->pop_back();
        }
    }

    // battle result info
    LogResultInfo(_output, current_army);
}

uint64_t BattleField::CalculateDamage(const Spaceship *shooter, const Spaceship *target) const
{
    // result damage calculation based on accuracy
    uint64_t damage = shooter->GetDamage();
    double current_ship_accuracy = shooter->GetAccuracy();
    // trying to hit the target, seed value from 0 to 1
    double rand_value = random_tool::RandomValueInRange(100) / 100.0;

    if (current_ship_accuracy < rand_value)
    {
        // missed
        return 0;
    }
    // if not missed
    else
    {
        // calculate damage based on evasion
        double target_ship_evasion = target->GetEvasion();
        // trying to evade, seed value from 0 to 1
        rand_value = random_tool::RandomValueInRange(100) / 100.0;

        if (target_ship_evasion < rand_value)
        {
            // evade not happens
            return damage;
        }
        else
        {
            return 0;
        }
    }
}

void BattleField::LogTurnResult(std::ostream &stream, const Spaceship *shooter, const Spaceship *target,
                                uint64_t damage) const
{
    if (shooter->GetFraction() == Spaceship::Fraction::Alliance)
    {
        stream << "Alliance: ";
    }
    else
    {
        stream << "Empire: ";
    }
    stream << shooter->GetName() << " shoots at " << target->GetName() << ". Result: " << damage << " damage, "
           << target->GetStrength() << " strength left." << std::endl;
}

void BattleField::LogResultInfo(std::ostream &stream, const Spaceships *current_army) const
{
    stream << "\n-----------------------------------------------------------------------------------------\n\n";

    if (_alliance_army.size() == 0)
    {
        stream << "Empire won." << std::endl;
    }
    else
    {
        stream << "Alliance won." << std::endl;
    }

    size_t shuttles_remain{};
    size_t transports_remain{};
    size_t scout_remain{};
    size_t fighter_remain{};
    size_t bomber_remain{};

    for (const auto &el : *current_army)
    {
        switch (el->GetType())
        {
        case Spaceship::SpaceshipType::Shuttle:
            ++shuttles_remain;
            break;
        case Spaceship::SpaceshipType::Transport:
            ++transports_remain;
            break;
        case Spaceship::SpaceshipType::Scout:
            ++scout_remain;
            break;
        case Spaceship::SpaceshipType::Fighter:
            ++fighter_remain;
            break;
        case Spaceship::SpaceshipType::Bomber:
            ++bomber_remain;
            break;
        }
    }

    stream << "Remaining spaceships: " << current_army->size() << "\n\nShuttle: " << shuttles_remain
           << "\nTransport: " << transports_remain << "\nScout: " << scout_remain << "\nFighter: " << fighter_remain
           << "\nBomber: " << bomber_remain << std::endl;
}
