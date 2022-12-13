/*
 * Authors: wilmi895, maxra518
 * Implements the interface code for the boggle game.
 * Uses and interacts with boggle class to update and retrieve game state.
 */

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <unordered_set>

#include "Boggle.h"
#include "bogglemain.h"

void drawBoggleBoard(Boggle const& boggle);
void drawPlayerScore(Boggle const& boggle);
bool isAlpha(string const& string);
void toUpper(string& string);
string getCustomBoardConfig();
void drawAiScore(Boggle const& boggle, set<string> const& foundWords);
void drawGameResults(Boggle const& boggle);
string quote(string const& text);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
	clearConsole();

	if (yesOrNo("Use custom configuration? (y/n): ")) {
		boggle.initBoard(getCustomBoardConfig());

	} else {
		boggle.initBoard();
	}

	clearConsole();

	while (true) {
		drawBoggleBoard(boggle);
		drawPlayerScore(boggle);
		cout << "Type a word (or press enter to end your turn): ";
		string guess;
		getline(cin, guess);
		cout << endl;

		if (guess.empty()) {
			break;
		}

		clearConsole();
		toUpper(guess);

		if (!boggle.isMinimumWordLength(guess)) {
			cout << "Word " << quote(guess)
				 << " is shorter than minimum length " << boggle.MIN_WORD_LENGTH
				 << '\n';

		} else if (!boggle.existsWord(guess)) {
			cout << "Word " << quote(guess)
				 << " does not exist in the lexicon\n";

		} else if (boggle.alreadyGuessedWord(guess)) {
			cout << "Word " << quote(guess) << " already guessed\n";

		} else if (boggle.findGuess(guess)) {
			cout << "You found a new word! " << quote(guess) << '\n';
		}
	}

	set<string> const remainingWords = boggle.findAllRemainingWords();
	drawAiScore(boggle, remainingWords);
	drawGameResults(boggle);
	boggle.resetGame();
}

/*
 * Gets a custom board configuration from the player.
 */
string getCustomBoardConfig() {
	string config;
	size_t const requiredConfigLength = Boggle::numCubes();
	config.reserve(requiredConfigLength);

	/*
	 * Configs for testing:
	 * BANAAANALEAALEVA
	 * TESTWORDAAAAAAAA
	 */

	while (true) {
		cout << "Enter " << requiredConfigLength << " characters to use: ";
		getline(cin, config);
		cout << endl;

		if (config.length() != requiredConfigLength) {
			cout << "Custom configuration has to be " << Boggle::numCubes()
				 << " characters\n";

		} else if (!isAlpha(config)) {
			cout << "Enter only alphanumeric characters\n";

		} else {
			break;
		}
	}

	toUpper(config);
	return config;
}

/*
 * Draws the game result depending on the scores in boggle.
 */
void drawGameResults(Boggle const& boggle) {
	int const playerScore = boggle.getPlayerScore();
	int const aiScore	  = boggle.getAiScore();

	if (playerScore < aiScore) {
		cout << "Ha ha ha, I destroyed you. Better luck next time, puny "
				"human!\n";

	} else if (playerScore > aiScore) {
		cout << "Oh.. you beat me? Impressive human.\n";

	} else {
		cout << "Somehow it's a tie!\n";
	}
}

/*
 * Draws the ai turns result after playing.
 */
void drawAiScore(Boggle const& boggle, set<string> const& foundWords) {
	cout << "It's my turn!!\n";
	cout << "My words (" << foundWords.size() << "):\n";
	cout << "{ ";

	for (string const& word : foundWords) {
		cout << quote(word) << " ";
	}

	cout << "}\n";
	cout << "My Score: " << boggle.getAiScore() << '\n';
}

/*
 * Checks if a string only contains alphabetic letters.
 */
bool isAlpha(string const& string) {
	return std::all_of(string.begin(), string.end(),
					   [](unsigned char const c) { return std::isalpha(c); });
}

/*
 * Converts a string to uppercase.
 */
void toUpper(string& string) {
	std::transform(string.begin(), string.end(), string.begin(),
				   [](unsigned char const c) { return std::toupper(c); });
}

/*
 * Draws the players current game result.
 */
void drawPlayerScore(Boggle const& boggle) {
	set<string> const& guessedWords = boggle.getGuessedWords();
	int const playerScore			= boggle.getPlayerScore();

	cout << "Your words(" << guessedWords.size() << "):\n";
	cout << "{ ";

	for (string const& word : guessedWords) {
		cout << quote(word) << " ";
	}

	cout << "}\n";
	cout << "Your Score: " << playerScore << endl;
}

/*
 * Draws the boggle board.
 */
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
 * Puts quotes around a string.
 */
string quote(string const& text) { return "\"" + text + "\""; }

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
