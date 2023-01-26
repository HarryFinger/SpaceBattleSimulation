#pragma once
#include <string>

class Spaceship
{

public:
    enum class SpaceshipType
    {
        Shuttle,
        Transport,
        Scout,
        Fighter,
        Bomber
    };

    enum class Fraction
    {
        Alliance,
        Empire
    };

    Spaceship(Fraction fraction, uint64_t strength, uint64_t damage, double accuracy, double evasion, const std::string& name);
    virtual ~Spaceship() = default;

    uint64_t GetDamage() const;
    uint64_t GetStrength() const;
    const std::string &GetName() const;
    virtual SpaceshipType GetType() const = 0;
    double GetAccuracy() const;
    double GetEvasion() const;
    void ApplyDamage(uint64_t damage);
    Fraction GetFraction() const;

protected:
    const std::string _name;
    Fraction _fraction;
    uint64_t _strength;
    uint64_t _damage;
    double _accuracy;
    double _evasion;
};
