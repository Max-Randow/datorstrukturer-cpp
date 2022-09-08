#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include<set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

set<string> init_dict(string const& file_name){

    set<string> dict_set;
    string buffer;
    ifstream rfile(file_name);

    // Setup set with given dictionary
    while(getline(rfile,buffer)){
        dict_set.insert(buffer);
    }
    rfile.close();
    return dict_set;
}


vector<string> word_neighbours(string const& word, set<string> const& dictionary){
    vector<string> neighbours;
    for(int i = 0; i < word.size(); i++){
        string tmp_word = word;
        for(char const& letter : ALPHABET){
            tmp_word[i] = letter;
            // Adds word to the neighbour list if it exists in the dictionary, the word itself is not a neighbour to itself
            if(dictionary.find(tmp_word) != dictionary.end() && tmp_word != word){
                neighbours.push_back(tmp_word);
            }

        }
    }
    return neighbours;
}

stack<string> word_chain(string const& word1, string const& word2, set<string> const& dictionary){
    // vars n bars (sick yao)
    queue<stack<string>> chain_queue;
    stack<string> first_chain;
    set<string> used_words;
    first_chain.push(word1);
    chain_queue.push(first_chain);

    while(!chain_queue.empty()){
        stack<string> part_chain = chain_queue.pop();
        if(part_chain.top() == word2) {
            return part_chain;
        }
       vector<string> neighbours = word_neighbours(part_chain.top(), dictionary);
       for(string const& word : neighbours){
            if(used_words.find(word) != used_words.end()){
                stack<string> chain_copy = part_chain;
                chain_copy.push(word);
                chain_queue.push(chain_copy);
                used_words.insert(word);
            }
       }
        

    }
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    const set<string> word_dict = init_dict("dictionary.txt");



    cout << "Please type two words: ";


    // TODO: Finish the program!

    return 0;
}
