#pragma once
#include <string>

// Game data struct (Handles save file)
struct GameData {
    int coins = 0;
    unsigned int highScore = 0;
    bool normalVictory = false;
    bool gameCompleted = false;
    bool hellVictory = false;
    int difficulty = 1;
    int equipedbullet = 0;
    std::string redbullet = "ACQUIRED";
    std::string bluebullet = "NULL";
    std::string greenbullet = "NULL";

    std::string yellowbullet = "NULL";
    std::string purplebullet = "NULL";
    std::string whitebullet = "NULL";
    std::string blackbullet = "NULL";
    int equipedship = 0;
    std::string normalship = "ACQUIRED";
    std::string blueship = "NULL";
    std::string greenship = "NULL";
    std::string yellowship = "NULL";
    std::string purpleship = "NULL";
    std::string redship = "NULL";
    std::string blackship = "NULL";
    int equipedfire = 0;
    std::string normalfire = "ACQUIRED";
    std::string yellowfire = "NULL";
    std::string greenfire = "NULL";
    std::string whitefire = "NULL";

};

// Functions
void updateGameData(const GameData& data);
GameData readFromFile();
void resetGameData();



