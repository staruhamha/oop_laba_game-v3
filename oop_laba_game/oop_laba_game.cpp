#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include "TerrainMap.h"
#include "TerrainTypes.h"
#include "GameFacade.h"
#include "GameField.h"
#include "Base.h"
#include "GameController.h"
#include <Windows.h>

using namespace std;

void clear() {
    system("cls");
}

void fillTerrainMap(TerrainMap& terrainMap) {
    for (int y = 0; y < terrainMap.getHeight(); y++) {
        for (int x = 0; x < terrainMap.getWidth(); x++) {
            terrainMap.setTerrain(x, y, std::make_unique<Plains>());
        }
    }

    for (int y = 1; y < 6; y++) {
        for (int x = 3; x < 7; x++) {
            terrainMap.setTerrain(x, y, std::make_unique<Forest>());
        }
    }

    for (int y = 8; y < 12; y++) {
        for (int x = 1; x < 6; x++) {
            terrainMap.setTerrain(x, y, std::make_unique<Swamp>());
        }
    }

    for (int y = 2; y < 7; y++) {
        for (int x = 10; x < 14; x++) {
            terrainMap.setTerrain(x, y, std::make_unique<Mountains>());
        }
    }
}

void printGameField(GameFacade& game, GameField& gameField, TerrainMap& terrainMap) {
    gameField.printField(game.getBase()->getUnits(), terrainMap);
}

void runAutomaticScenario(GameFacade& game, GameField& gameField, TerrainMap& terrainMap, int scenario) {
    vector<string> commands;

    switch (scenario) {
    case 1:
        commands = {
            "create unit infantry at 5,5",
            "stats units"
        };
        break;

    case 2:
        commands = {
            "create unit scout at 6,5",
            "create unit infantry at 7,5",
            "move unit 1 to 10,10",
            "attack unit 1 target 2",
            "stats units"
        };
        break;

    case 3:
        commands = {
            "build barracks at 3,3",
            "build laboratory at 2,2",
            "research attack_upgrade",
            "produce infantry in 1",
            "stats buildings"
        };
        break;

    case 4:
        commands = {
            "collect unit 1 from 1",
            "distribute wood to barracks 50",
            "stats resources",
            "stats buildings"
        };
        break;
    }

    for (const string& command : commands) {
        clear();

        cout << "Автоматический сценарий\n";
        cout << "Команда: " << command << "\n\n";

        printGameField(game, gameField, terrainMap);

        cout << "\nРезультат:\n";
        game.processInput(command);

        cout << "\nНажми Enter для продолжения";
        cin.get();
    }
}

void runScenario(GameFacade& game, GameField& gameField, TerrainMap& terrainMap, const string& title, int scenario) {
    int mode;

    clear();

    cout << title << "\n\n";
    cout << "1. Автоматический сценарий\n";
    cout << "2. Ручное управление\n";
    cout << "0. Назад\n\n";
    cout << "> ";

    cin >> mode;
    cin.ignore(10000, '\n');

    if (mode == 1) {
        runAutomaticScenario(game, gameField, terrainMap, scenario);
    }
    else if (mode == 2) {
        string command;

        while (true) {
            clear();

            cout << title << "\n\n";
            printGameField(game, gameField, terrainMap);

            cout << "\nКоманды: create, move, attack, collect, heal, build, research, produce, distribute, stats\n";
            cout << "Для возврата в меню введи menu\n";

            cout << "\n> ";
            getline(cin, command);

            if (command == "menu") {
                break;
            }

            if (command.empty()) {
                continue;
            }

            game.processInput(command);

            cout << "\nНажми Enter для продолжения";
            cin.get();
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));

    auto gameController = std::make_shared<GameController>(1000, 5, 0, 100, 15, 15);
    GameFacade game(gameController);

    GameField gameField(15, 15);
    TerrainMap& terrainMap = gameController->getTerrainMap();

    fillTerrainMap(terrainMap);

    int choice;

    while (true) {
        clear();

        printGameField(game, gameField, terrainMap);
        cout << "\n";

        cout << "1. Управление юнитами\n";
        cout << "2. Боевые действия\n";
        cout << "3. Управление базой\n";
        cout << "4. Просмотр статистики\n";
        cout << "0. Выход\n";

        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {

        case 0: {
            return 0;
        }

        case 1: {
            runScenario(game, gameField, terrainMap, "Управление юнитами", 1);
            break;
        }

        case 2: {
            runScenario(game, gameField, terrainMap, "Боевые действия", 2);
            break;
        }

        case 3: {
            runScenario(game, gameField, terrainMap, "Управление базой", 3);
            break;
        }

        case 4: {
            runScenario(game, gameField, terrainMap, "Просмотр статистики", 4);
            break;
        }

        default: {
            cout << "Неверный пункт меню\n";
            cin.get();
            break;
        }

        }
    }

    return 0;
}
