#include "BattleField.h"
#include "AllianceFactory.h"
#include "EmpireFactory.h"
#include "RandomTool.h"
#include <iostream>
#include <random>

BattleField::BattleField(std::ifstream &settings_file)
{
    output.open("output.txt");
    _val = boost::json::parse(settings_file);
    CreateArmy(Spaceship::Fraction::Alliance);
    CreateArmy(Spaceship::Fraction::Empire);
}

void BattleField::CreateArmy(Spaceship::Fraction fraction)
{
    std::unique_ptr<SpaceshipFactory> factory;
    std::string fraction_type;
    Spaceships *spaceships = nullptr;
    std::string frac_posfix;

    switch (fraction)
    {
    case Spaceship::Fraction::Alliance:
        factory = std::make_unique<AllianceFactory>();
        fraction_type = "Alliance";
        spaceships = &_alliance_army;
        frac_posfix = "-A";
        break;
    case Spaceship::Fraction::Empire:
        factory = std::make_unique<EmpireFactory>();
        fraction_type = "Empire";
        spaceships = &_empire_army;
        frac_posfix = "-E";
        break;
    }

    Data data;
    boost::json::value json;
    std::string name;
    size_t spaceship_id = 1;

    name = "Shuttle";
    json = _val.as_object()[fraction_type].as_object()[name];
    data.Load(json);
    for (size_t i = 0; i < data.count; i++)
    {
        spaceships->push_back(factory->CreateSpaceship(Spaceship::SpaceshipType::Shuttle, data.strength, data.damage,
                                                       data.accuracy, data.evasion,
                                                       name + frac_posfix + std::to_string(spaceship_id++)));
    }

    name = "Transport";
    json = _val.as_object()[fraction_type].as_object()[name];
    data.Load(json);
    for (size_t i = 0; i < data.count; i++)
    {
        spaceships->push_back(factory->CreateSpaceship(Spaceship::SpaceshipType::Transport, data.strength, data.damage,
                                                       data.accuracy, data.evasion,
                                                       name + frac_posfix + std::to_string(spaceship_id++)));
    }

    name = "Scout";
    json = _val.as_object()[fraction_type].as_object()[name];
    data.Load(json);
    for (size_t i = 0; i < data.count; i++)
    {
        spaceships->push_back(factory->CreateSpaceship(Spaceship::SpaceshipType::Scout, data.strength, data.damage,
                                                       data.accuracy, data.evasion,
                                                       name + frac_posfix + std::to_string(spaceship_id++)));
    }

    name = "Fighter";
    json = _val.as_object()[fraction_type].as_object()[name];
    data.Load(json);
    for (size_t i = 0; i < data.count; i++)
    {
        spaceships->push_back(factory->CreateSpaceship(Spaceship::SpaceshipType::Fighter, data.strength, data.damage,
                                                       data.accuracy, data.evasion,
                                                       name + frac_posfix + std::to_string(spaceship_id++)));
    }

    name = "Bomber";
    json = _val.as_object()[fraction_type].as_object()[name];
    data.Load(json);
    for (size_t i = 0; i < data.count; i++)
    {
        spaceships->push_back(factory->CreateSpaceship(Spaceship::SpaceshipType::Bomber, data.strength, data.damage,
                                                       data.accuracy, data.evasion,
                                                       name + frac_posfix + std::to_string(spaceship_id++)));
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
        LogTurnResult(output, shooter, target, damage);

        // destroy target army spaceship if strength is less or equal to 0
        if (target->GetStrength() == 0)
        {
            std::swap((*target_army)[target_ship_index], (*target_army)[target_army_size - 1]);
            target_army->pop_back();
        }
    }

    // battle result info
    LogResultInfo(output, current_army);
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

void BattleField::Data::Load(boost::json::value &json)
{
    strength = (uint64_t)json.as_object()["Strength"].as_int64();
    damage = (uint64_t)json.as_object()["Damage"].as_int64();
    accuracy = json.as_object()["Accuracy"].as_double();
    evasion = json.as_object()["Evasion"].as_double();
    count = (uint64_t)json.as_object()["Count"].as_int64();
}