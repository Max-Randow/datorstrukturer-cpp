/*
 * Author: wilmi895, maxra518
 * Lab 2b: Evil Hangman
 * Description:
 * Plays evil hangman game. Asks user for guess and filters word
 * to make guesses incorrect and harder to guess word, thus winning.
 * User can play multiple times, choose word lenght, amount of guesses
 * and if they want to see the possible words to guess.
 */
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
pair<vector<string>, unordered_set<unsigned int>> init_dictionary(
	string const& file_name) noexcept {
	ifstream rfile(file_name);
	vector<string> dictionary;
	unordered_set<unsigned int> word_lengths;
	string buffer;

	while (getline(rfile, buffer)) {
		dictionary.push_back(buffer);
		word_lengths.insert(static_cast<unsigned int>(buffer.length()));
	}
	return make_pair(dictionary, word_lengths);
}

/*
 * Checks if letter is alphabetic.
 */
bool inAlphabet(char const letter) noexcept {
	return binary_search(ALPHABET.cbegin(), ALPHABET.cend(), letter);
}

/*
 * Asks users yes or no question.
 */
bool ask_user_yes_no(string const& message) noexcept {
	string choice;

	while (true) {
		cout << message << " (y/n): ";
		cin >> choice;

		if (choice == "y") {
			return true;
		}
		if (choice == "n") {
			return false;
		}
	}
}

/*
 * Holds game settings for initializing game.
 */
struct GameSettings {
	bool const show_words_left;
	unsigned int const word_length;
	unsigned int const guess_count;
};

/*
 * Sets up game settings and retrieves them from the user.
 */
GameSettings setup_game(unordered_set<unsigned int> const& word_lengths) {
	unsigned int wanted_word_len = 0;
	// Get the word length from user.
	while (true) {
		cout << "Choose the word length: ";
		cin >> wanted_word_len;
		// the iterator did not reach the end thus we found our target, break
		// and continue the program
		if (word_lengths.find(wanted_word_len) != word_lengths.cend()) {
			break;
		}
		cout << "No words exist with length " << wanted_word_len << '\n';
	}

	unsigned int guess_count = 0;
	// Get number of guesses from user.
	while (true) {
		cout << "Choose amount of guesses: ";
		cin >> guess_count;

		if (guess_count > 0) {
			break;
		}
		cout << "Guesses have to be greater than 0!\n";
	}

	bool const show_words_left =
		ask_user_yes_no("Show words left after each guess?");

	return {show_words_left, wanted_word_len, guess_count};
}

/*
 * Holds data about a word family.
 */
struct WordFamliyData {
	vector<string> word_family;
	string family_key;
};

/*
 * Generates word families and picks out the largest family.
 */
WordFamliyData gen_largest_word_family(vector<string> const& dictionary,
									   char const guess) {
	unordered_map<string, vector<string>> word_families;
	string largest_family_key;
	unsigned int largest_family_size = 0;
	size_t const word_length		 = dictionary[0].length();

	for (string const& word : dictionary) {
		string family_key;
		// Construct family key for word using letters which match guess.
		// If our guess matches a letter in a word, save the position of the
		// letter and add it as a key, no match is represented as '-', ex :
		// family_key = "-a--" and
		for (unsigned int i = 0; i < word_length; ++i) {
			if (word[i] == guess) {
				family_key += guess;
			} else {
				family_key += '-';
			}
		}
		vector<string>& current_family = word_families[family_key];
		current_family.push_back(word);
		// Save largest family.
		if (current_family.size() > largest_family_size) {
			largest_family_size =
				static_cast<unsigned int>(current_family.size());
			largest_family_key = move(family_key);
		}
	}

	return WordFamliyData {word_families[largest_family_key],
						   largest_family_key};
}

/*
 * Asks the user for the next guess and checks if it is valid
 * before returning it.
 */
char get_next_guess(set<char> const& guessed_letters) {
	char guess = ' ';
	while (true) {
		cout << "Enter guess: ";
		string buffer;
		cin >> buffer;

		// Check if user entered only one character.
		if (buffer.length() > 1) {
			cout << "Guess a single character.\n";
			continue;
		}
		guess = buffer[0];

		// Check if guess is a valid character.
		if (!inAlphabet(guess)) {
			cout << "Character not in alphabet.\n";
		} else if (guessed_letters.find(guess) != guessed_letters.cend()) {
			cout << "Letter already guessed, guess another.\n";
		} else {
			return guess;
		}
	}
}

/*
 * Contains the the current word guessed
 * and the amount of correctly guessed letters.
 */
struct WordData {
	string current_word;
	unsigned int const correct_letter_count;
};

/*
 * Merges letters of two words. If both have character '-' at the same position
 * keep it. Both words must have the same length and both words do not have a
 * letter at the same index.
 */
WordData update_current_word(string const& current_word,
							 string const& newly_guessed) {
	size_t const word_length = current_word.length();
	// Skapa en template str??ng som bara ??r word_length antal '-'
	string updated_word(word_length, '-');
	unsigned int correct_letter_count = 0;

	// Merge letters in both words and count them.
	for (size_t i = 0; i < word_length; ++i) {
		if (current_word[i] != '-') {
			updated_word[i] = current_word[i];
			correct_letter_count++;
		} else if (newly_guessed[i] != '-') {
			updated_word[i] = newly_guessed[i];
			correct_letter_count++;
		}
	}
	return {updated_word, correct_letter_count};
}

/*
 * The main game loop of hangman.
 */
void game_loop(vector<string> const& dictionary,
			   unordered_set<unsigned int> const& word_lengths) {
	// Game loop.
	do {
		GameSettings const settings = setup_game(word_lengths);
		set<char> guessed_letters;
		unsigned int correct_letters = 0;
		unsigned int guesses_left	 = settings.guess_count;
		string current_word(settings.word_length, '-');

		// Extract words with provided length.
		vector<string> current_word_family;
		copy_if(dictionary.cbegin(), dictionary.cend(),
				back_inserter(current_word_family),
				[&settings](string const& word) noexcept {
					return word.length() == settings.word_length;
				});

		// Guess loop.
		while (true) {
			cout << "------------------------------------------\n";
			cout << "Guesses left: " << guesses_left << '\n';
			cout << "Letters guessed: ";
			for (char const letter : guessed_letters) {
				cout << letter << ' ';
			}
			cout << '\n';
			cout << current_word << '\n';

			// Display possible words left.
			if (settings.show_words_left) {
				for (string const& word : current_word_family) {
					cout << word << ' ';
				}
				cout << '\n';
			}

			// Check if all letters have been found.
			if (correct_letters == settings.word_length) {
				cout << "You win!\n";
				break;
			}
			// Check if no guess attempts are left.
			if (guesses_left == 0) {
				cout << "You lost\n";
				break;
			}

			// Retrieve the next guess from player.
			char const guess = get_next_guess(guessed_letters);
			guessed_letters.insert(guess);

			WordFamliyData family_data =
				gen_largest_word_family(current_word_family, guess);

			// NOTE: move does not make a copy, makes current (moved value)
			// invalid afterwards
			current_word_family = move(family_data.word_family);

			WordData updated_word_data =
				update_current_word(current_word, family_data.family_key);
			current_word = move(updated_word_data.current_word);

			// If correct letters guessed did not change, it was
			// an incorrect guess.
			if (correct_letters == updated_word_data.correct_letter_count) {
				guesses_left--;
			} else {  // Correct letters guessed changed, update it (should
					  // always increase).
				correct_letters = updated_word_data.correct_letter_count;
			}
		}
	} while (ask_user_yes_no("Play again?"));
}

int main() {
	// Initialize dictionary and set of available word lengths.
	auto init_pair					= init_dictionary("dictionary.txt");
	vector<string> const dictionary = move(init_pair.first);
	unordered_set<unsigned int> const word_lengths = move(init_pair.second);

	cout << "Welcome to Hangman.\n";

	game_loop(dictionary, word_lengths);

	// Ut??kning: Vikt ordklasser med hur m??nga unika bokst??ver de
	// har.
	//  Har vissa ord multipla bokst??ver kommer de kr??vas f??rre
	//  gissningar

	return 0;
}
