#include "BattleField.h"
#include "RandomTool.h"
#include <fstream>

int main()
{

    std::ifstream settings_file;
    settings_file.open("settings.json");

    BattleField battle_field(settings_file);
    battle_field.SimulateBattle();

    settings_file.close();
}