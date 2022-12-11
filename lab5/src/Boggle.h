// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
	const string DICTIONARY_FILE = "EnglishWords.dat";
	const int MIN_WORD_LENGTH	 = 4;
	const int BOARD_SIZE		 = 4;

	Boggle();

	Grid<char> const& getBoard() const;
	void initBoard(string const& cubes);
	void initBoard();
	void resetGame();
	static int numCubes();
	bool existsWord(string const& word) const;
	bool isMinimumWordLength(string const& word) const;
	bool alreadyGuessedWord(string const& word) const;

	int getPlayerScore() const;
	int getAiScore() const;

	set<string> const& getGuessedWords() const;
	bool findGuess(string const& word);
	set<string> findAllRemainingWords();


private:
	Grid<char> board;
	Lexicon lexicon;
	int playerScore = 0;
	int aiScore		= 0;
	set<string> guessedWords;
	set<pair<int, int>> visited;

	vector<pair<int, int>> getNeighbors(pair<int, int> const& node) const;
	void searchRemainingWords(string const& word,
							  pair<int, int> const& node,
							  set<string>& foundWords);
	bool searchWord(string const& word,
					int wordIndex,
					pair<int, int> const& node);
	bool alreadyVisited(pair<int, int> const& node) const;
	void updateAiScore(string const& word);
	void updatePlayerScore(string const& word);
};

#endif
