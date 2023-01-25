#include "Spaceship.h"

Spaceship::Spaceship(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion,
                     const std::string &name)
    : _fraction(fraction), _strength(strength), _damage(damage), _accuracy(accuracy), _evasion(evasion), _name(name)
{
}


uint64_t Spaceship::GetDamage() const
{
    return _damage;
}

uint64_t Spaceship::GetStrength() const
{
    return _strength;
}

const std::string& Spaceship::GetName() const
{
    return _name;
}

double Spaceship::GetAccuracy() const
{
    return _accuracy;
}

double Spaceship::GetEvasion() const
{
    return _evasion;
}

void Spaceship::ApplyDamage(uint64_t damage)
{
    if (_strength > damage)
    {
        _strength -= damage;
    }
    else
    {
        _strength = 0;
    }
}

Spaceship::Fraction Spaceship::GetFraction() const
{
    return _fraction;
}
