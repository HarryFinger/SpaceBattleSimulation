#include "BattleField.h"
#include "SpaceshipsData.h"
#include "RandomTool.h"
#include <fstream>

int main()
{

    std::ifstream settings_file;
    settings_file.open("settings.json");
    SpaceshipsData spaceships_data(settings_file);

    BattleField battle_field(&spaceships_data);
    battle_field.SimulateBattle();

    settings_file.close();
}