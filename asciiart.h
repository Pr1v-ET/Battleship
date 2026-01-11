#pragma once

#include <map>
#include <vector>
#include <string>
#include <curses.h>

class AsciiArt {
private:
    std::map<char, std::vector<std::string>> letters;
    int currentY = 3;
    int letterHeight = 5;
    int letterWidth = 7;

public:
    AsciiArt();
    void setY(int y) { currentY = y; }
    int getY() const { return currentY; }
    void print(const std::string& text, int cols);
    int getTextWidth(const std::string& text) const;
    static std::string toUpper(const std::string& str);
};