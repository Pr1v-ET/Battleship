#pragma once

#include <string>

class Game {
private:
    enum class modeVariant { PvP, PvAI };
    enum class difficultyVariant { Easy, Medium, Hard };
    modeVariant mode;
    difficultyVariant aiDifficulty;

public:
    Game();
    bool isPvAI() const { return mode == modeVariant::PvAI; }
    std::string getMode() const {
        switch (mode) {
            case modeVariant::PvP:
                return "(PvP)";
            case modeVariant::PvAI:
                return "(PvAI)";
        }
        return "";
    }
    int getModeIndex() const {
        switch (mode) {
            case modeVariant::PvP:
                return 0;
            case modeVariant::PvAI:
                return 1;
        }
        return -1;
    }
    void setMode(int newMode) {
        switch (newMode) {
            case 0:
                mode = modeVariant::PvP;
                break;
            case 1:
                mode = modeVariant::PvAI;
                break;
        }
    }
    std::string getDifficulty() const {
        switch (aiDifficulty) {
            case difficultyVariant::Easy:
                return "(Ë¸ãêàÿ)";
            case difficultyVariant::Medium:
                return "(Ñðåäíÿÿ)";
            case difficultyVariant::Hard:
                return "(Òÿæ¸ëàÿ)";
        }
        return "";
    }
    int getDifficultyIndex() const {
        switch (aiDifficulty) {
            case difficultyVariant::Easy:
                return 0;
            case difficultyVariant::Medium:
                return 1;
            case difficultyVariant::Hard:
                return 2;
        }
        return -1;
    }
    void setDifficulty(int newDifficulty) {
        switch (newDifficulty) {
            case 0:
                aiDifficulty = difficultyVariant::Easy;
                break;
            case 1:
                aiDifficulty = difficultyVariant::Medium;
                break;
            case 2:
                aiDifficulty = difficultyVariant::Hard;
                break;
        }
    }

};