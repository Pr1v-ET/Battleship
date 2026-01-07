#include "asciiart.h"

AsciiArt::AsciiArt() {
    letters['A'] = {
       " ### ",
       "#   #",
       "#####",
       "#   #",
       "#   #"
    };
    letters['B'] = {
        "#### ",
        "#   #",
        "#### ",
        "#   #",
        "#### "
    };
    letters['C'] = {
       " ####",
       "#    ",
       "#    ",
       "#    ",
       " ####"
    };
    letters['D'] = {
        "#### ",
        "#   #",
        "#   #",
        "#   #",
        "#### "
    };
    letters['E'] = {
        "#####",
        "#    ",
        "#### ",
        "#    ",
        "#####"
    };
    letters['F'] = {
        "#####",
        "#    ",
        "#### ",
        "#    ",
        "#    "
    };
    letters['G'] = {
        " ####",
        "#    ",
        "#  ##",
        "#   #",
        " ####"
    };
    letters['H'] = {
        "#   #",
        "#   #",
        "#####",
        "#   #",
        "#   #"
    };
    letters['I'] = {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "#####"
    };
    letters['J'] = {
        "#####",
        "   # ",
        "   # ",
        "#  # ",
        " ##  "
    };
    letters['K'] = {
        "#   #",
        "#  # ",
        "###  ",
        "#  # ",
        "#   #"
    };
    letters['L'] = {
        "#    ",
        "#    ",
        "#    ",
        "#    ",
        "#####"
    };
    letters['M'] = {
        "#   #",
        "## ##",
        "# # #",
        "#   #",
        "#   #"
    };
    letters['N'] = {
        "#   #",
        "##  #",
        "# # #",
        "#  ##",
        "#   #"
    };
    letters['O'] = {
        " ### ",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    };
    letters['P'] = {
        "#### ",
        "#   #",
        "#### ",
        "#    ",
        "#    "
    };
    letters['Q'] = {
        " ### ",
        "#   #",
        "#   #",
        "#  ##",
        " ####"
    };
    letters['R'] = {
        "#### ",
        "#   #",
        "#### ",
        "#  # ",
        "#   #"
    };
    letters['S'] = {
        " ####",
        "#    ",
        " ### ",
        "    #",
        "#### "
    };
    letters['T'] = {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  "
    };
    letters['U'] = {
        "#   #",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    };
    letters['V'] = {
        "#   #",
        "#   #",
        "#   #",
        " # # ",
        "  #  "
    };
    letters['W'] = {
        "#   #",
        "#   #",
        "# # #",
        "## ##",
        "#   #"
    };
    letters['X'] = {
        "#   #",
        " # # ",
        "  #  ",
        " # # ",
        "#   #"
    };
    letters['Y'] = {
        "#   #",
        " # # ",
        "  #  ",
        "  #  ",
        "  #  "
    };
    letters['Y'] = {
        "#####",
        "   # ",
        "  #  ",
        " #   ",
        "#####"
    };

    letters['0'] = {
        " ### ",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    };

    letters['1'] = {
        "  #  ",
        " ##  ",
        "  #  ",
        "  #  ",
        " ### "
    };

    letters['2'] = {
        " ### ",
        "#   #",
        "   # ",
        "  #  ",
        "#####"
    };

    letters['3'] = {
        " ### ",
        "#   #",
        "   ##",
        "#   #",
        " ### "
    };

    letters['4'] = {
        "#   #",
        "#   #",
        "#####",
        "    #",
        "    #"
    };

    letters['5'] = {
        "#####",
        "#    ",
        "#### ",
        "    #",
        "#### "
    };

    letters['6'] = {
        " ### ",
        "#    ",
        "#### ",
        "#   #",
        " ### "
    };

    letters['7'] = {
        "#####",
        "   # ",
        "  #  ",
        " #   ",
        " #   "
    };

    letters['8'] = {
        " ### ",
        "#   #",
        " ### ",
        "#   #",
        " ### "
    };

    letters['9'] = {
        " ### ",
        "#   #",
        " ####",
        "    #",
        " ### "
    };

}

void AsciiArt::print(const std::string& text, int cols) {
    std::string upperText = toUpper(text);
    int centerX = (cols - getTextWidth(upperText)) / 2;
    for (char c : upperText) {
        auto it = letters.find(c);
        if (it != letters.end()) {
            const auto& lines = it->second;
            for (int i = 0; i < letterHeight; i++) {
                mvprintw(currentY + i, centerX, "%s", lines[i].c_str());
            }
        }
        centerX += letterWidth;
    }
}

int AsciiArt::getTextWidth(const std::string& text) const {
    return text.length() * letterWidth;
}


std::string AsciiArt::toUpper(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        if (c >= 'a' && c <= 'z') {
            c = c - 32;
        }
    }
    return result;
}
