// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

bool isCorrectBoardConfig(string const& config) {
    return config.length() == 16 && std::all_of(config.begin(), config.end(),
                                               [](unsigned char c){ return std::isalpha(c); });
}

void askCustomBoardConfig(Boggle& boggle) {
    if(!yesOrNo("Use custom configuration?")){
        return;
    }
    while(true) {
            cout<<"Enter 16 characters to use:\n";
            string config;
            cin>>config;
            if(isCorrectBoardConfig(config)) {
                // Convert config string to lowercase.
                std::transform(config.begin(), config.end(), config.begin(),
                    [](unsigned char c){ return std::tolower(c); });
                boggle.initBoard(config);
                break;
            }

            cout << "Enter only alphanumeric characters\n";
      }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    askCustomBoardConfig(boggle);
}

void drawBoggleBoard(Boggle const& boggle) {
    Grid<char> board = boggle.getBoard();

    for(int i = 0; i < board.nCols; i++) {
        for(int j = 0; j < board.nCols; j++) {
            cout << board.get(i,j);
        }
        cout << '\n';
    }
    cout << '\n';
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}