#include "AllianceFactory.h"
#include "Bomber.h"
#include "Fighter.h"
#include "Scout.h"
#include "Shuttle.h"
#include "Transport.h"

std::unique_ptr<Spaceship> AllianceFactory::CreateSpaceship(Spaceship::SpaceshipType spaceship_type, uint64_t strength,
                                                             uint64_t damage, double accuracy, double evasion,
                                                             const std::string &name)
{
    Spaceship::Fraction fraction = Spaceship::Fraction::Alliance;
    switch (spaceship_type)
    {
    case Spaceship::SpaceshipType::Shuttle:
        return std::make_unique<Shuttle>(fraction, strength, damage, accuracy, evasion, name);
    case Spaceship::SpaceshipType::Transport:
        return std::make_unique<Transport>(fraction, strength, damage, accuracy, evasion, name);
    case Spaceship::SpaceshipType::Scout:
        return std::make_unique<Scout>(fraction, strength, damage, accuracy, evasion, name);
    case Spaceship::SpaceshipType::Fighter:
        return std::make_unique<Fighter>(fraction, strength, damage, accuracy, evasion, name);
    case Spaceship::SpaceshipType::Bomber:
        return std::make_unique<Bomber>(fraction, strength, damage, accuracy, evasion, name);
    default:
        return nullptr;
    }
}
