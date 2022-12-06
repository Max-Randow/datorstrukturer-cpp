// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <unordered_set>

#include "Boggle.h"
#include "bogglemain.h"

void drawBoggleBoard(Boggle const& boggle);
void drawScore(Boggle const& boggle);
bool isAlpha(string const& string);
void toLower(string& string);
bool useCustomBoardConfig(Boggle& boggle);


/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
	if (!useCustomBoardConfig(boggle)) {
		boggle.initBoard();
	}

	while (true) {
		drawBoggleBoard(boggle);
		drawScore(boggle);
		cout << "Type a word (or press enter to end your turn): \n";
		string guess;
		cin >> guess;

		if (guess.empty()) {
			break;
		}
		if (!boggle.validWord(guess)) {
			cout << "Invalid Word, guess again\n";
		} else if (boggle.alreadyGuessedWord(guess)) {
			cout << "Word already guessed\n";
		} else {
			cout << "Guess found: " << boggle.findGuess(guess) << "\n\n";
		}
	}
}

bool useCustomBoardConfig(Boggle& boggle) {
	if (!yesOrNo("Use custom configuration?")) {
		return false;
	}
	while (true) {
		cout << "Enter 16 characters to use:\n";
		string config;
		cin >> config;

		if (!(config.length() == Boggle::numCubes())) {
			cout << "Custom configuration has to be " << Boggle::numCubes()
				 << " characters\n";
		} else if (!isAlpha(config)) {
			cout << "Enter only alphanumeric characters\n";
		} else {
			toLower(config);
			boggle.initBoard(config);
			break;
		}
	}

	return true;
}

bool isAlpha(string const& string) {
	return std::all_of(string.begin(), string.end(),
					   [](unsigned char c) { return std::isalpha(c); });
}

void toLower(string& string) {
	std::transform(string.begin(), string.end(), string.begin(),
				   [](unsigned char c) { return std::tolower(c); });
}

void drawScore(Boggle const& boggle) {
	unordered_set<string> const& guessedWords = boggle.getGuessedWords();
	int const playerScore					  = boggle.getPlayerScore();

	cout << "Your words(" << guessedWords.size() << "):\n";
	cout << "{" << endl;
	for (string const& word : guessedWords) {
		cout << word << " ";
	}
	cout << "}\n";
	cout << "Your Score: " << playerScore << endl;
}

void drawBoggleBoard(Boggle const& boggle) {
	Grid<char> const& board = boggle.getBoard();

	for (int i = 0; i < board.nRows; i++) {
		for (int j = 0; j < board.nCols; j++) {
			cout << board.get(i, j);
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
