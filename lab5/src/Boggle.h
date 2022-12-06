// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <unordered_set>
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

	Grid<char> getBoard() const;
	void initBoard(string cubes);
	void initBoard();
	static int numCubes();
	bool validWord(const string& word) const;
	int getPlayerScore() const;
	int getAiScore() const;
	unordered_set<string> const& getGuessedWords() const;
	bool alreadyGuessedWord(string const& word) const;
	bool findValidWord(string const& word) const;
	vector<string> findAllRemainingWords() const;  // Kanske inte const
	void updatePlayerScore(string const& word);
	vector<pair<int, int>> getNeighbors(int const i, int const j) const;
	
	

private:
	Grid<char> board;
	Lexicon lexicon;
	int playerScore = 0;
	int aiScore		= 0;
	unordered_set<string> guessedWords;
};

#endif
