#include "BattleField.h"
#include "RandomTool.h"
#include "SpaceshipsData.h"

int main()
{
    SpaceshipsData spaceships_data;

    BattleField battle_field(&spaceships_data);
    battle_field.SimulateBattle();
}