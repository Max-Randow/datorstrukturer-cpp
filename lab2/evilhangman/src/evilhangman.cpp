#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";


/*
 * Initializes the english dictionary and a set of available word lengths
 * in the dictionary.
 */
pair<vector<string>, unordered_set<size_t>> init_dictionary(
	string const& file_name) {
	ifstream rfile(file_name);
	vector<string> dictionary;
	unordered_set<size_t> word_lengths;
	string buffer;

	while (getline(rfile, buffer)) {
		dictionary.push_back(buffer);
		word_lengths.insert(buffer.length());
	}
	return make_pair(dictionary, word_lengths);
}

bool inAlphabet(char letter) {
	// ALPHABET.find_first_of(letter);
	for (char l : ALPHABET) {
		if (l == letter) {
			return true;
		}
	}
	return false;
}

struct GameSettings {
	bool show_words_left;
	size_t word_length;
	int guess_count;
};

bool AskUserYesNo(string const& message) {
	string choice;

	while (true) {
		cout << message << " (y/n): ";
		cin >> choice;

		if (choice == "y") {
			return true;
		} else if (choice == "n") {
			return false;
		}
	}
}

GameSettings setup_game(unordered_set<size_t> const& word_lengths) {
	size_t wanted_word_len = 0;

	while (true) {
		cout << "Choose the word size: ";
		cin >> wanted_word_len;

		if (word_lengths.find(wanted_word_len) != word_lengths.end()) {
			break;
		}
		cout << "No words exist with length " << wanted_word_len << '\n';
	}


	int guess_count = 0;

	while (true) {
		cout << "Choose amount of guesses: ";
		cin >> guess_count;

		if (guess_count > 0) {
			break;
		}
		cout << "Guesses have to be greater than 0!\n";
	}

	bool show_words_left = AskUserYesNo("Show words left after each guess?");

	return {show_words_left, wanted_word_len, guess_count};
}

void game_loop(vector<string> const& dictionary,
			   unordered_set<size_t> const& word_lengths) {
	while (true) {
		set<char> guessed_letters;
		GameSettings settings = setup_game(word_lengths);
		string current_word_version(settings.word_length, '-');
		int guesses_left = settings.guess_count;

		vector<string> equal_len_words;
		copy_if(dictionary.cbegin(), dictionary.cend(),
				back_inserter(equal_len_words),
				[&settings](string const& word) {
					return word.length() == settings.word_length;
				});

		cout << "Guesses left: " << guesses_left << '\n';
		cout << "Letters guessed: ";
		for (char letter : guessed_letters) {
			cout << letter << ' ';
		}
		cout << endl;
		cout << current_word_version << '\n';
		// TODO: fix write out words left after guess :)

		string guess;
		while (true) {
			cout << "Enter guess: ";
			cin >> guess;

			if (!inAlphabet(guess[0])) {
				cout << "Not a valid character.\n";
			}

			if (guessed_letters.find(guess[0]) != guessed_letters.end()) {
				break;
			} else {
				cout << "Letter already guessed, guess another letter.\n";
			}
		}

		// TODO: partition words


		if (!AskUserYesNo("Play again?")) {
			break;
		}
	}

	"-E--"
		// Maps string with indicies of equal letters to word families.
		unordered_map<string, vector<string>>
			word_families;
	// The same but the size of each family.
	unordered_map<string, size_t> word_familiy_sizes;
}

int main() {
	auto init_pair					= init_dictionary("dictionary.txt");
	vector<string> const dictionary = move(init_pair.first);
	unordered_set<size_t> const word_lengths = move(init_pair.second);

	cout << "Welcome to Hangman.\n";

	game_loop(dictionary, word_lengths);

	return 0;
}
