// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"

#include <queue>
#include <sstream>
#include <string>

using namespace std;

/*
 * Build huffman frequency table from stream input.
 */
map<int, int> buildFrequencyTable(istream& input) {
	map<int, int> freqTable;
	int character = input.get();

	while (!input.fail()) {
		freqTable[character]++;
		character = input.get();
	}
	freqTable[PSEUDO_EOF] = 1;
	return freqTable;
}


HuffmanNode* buildEncodingTree(map<int, int> const& freqTable) {
	priority_queue<HuffmanNode> heap {};

	for (auto const& charFreq : freqTable) {
		heap.push(HuffmanNode(charFreq.first, charFreq.second));
	}

	// Continually join two nodes in a root node to create the tree.
	while (heap.size() > 1) {
		HuffmanNode root {};

		root.zero = new HuffmanNode(heap.top());
		heap.pop();
		root.one = new HuffmanNode(heap.top());
		heap.pop();
		root.count = root.zero->count + root.one->count;

		heap.push(root);
	}

	return new HuffmanNode(heap.top());
}

void buildEncodingMapHelper(HuffmanNode const* const root,
							string encoding,
							map<int, string>& encodingMap) {
	if (root->isLeaf()) {
		encodingMap[root->character] = move(encoding);
		return;
	}

	buildEncodingMapHelper(root->zero, encoding + "0", encodingMap);
	buildEncodingMapHelper(root->one, encoding + "1", encodingMap);
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
	map<int, string> encodingMap;

	buildEncodingMapHelper(encodingTree, "", encodingMap);

	return encodingMap;
}

int asciiToDecimal(char const ascii) { return ascii - '0'; }

void writeBits(string const& input, obitstream& output) {
	for (char const bit : input) {
		// Convert ascii to decimal
		output.writeBit(asciiToDecimal(bit));
	}
}

void encodeData(istream& input,
				map<int, string> const& encodingMap,
				obitstream& output) {
	int character = input.get();

	while (!input.fail()) {
		writeBits(encodingMap.at(character), output);
		character = input.get();
	}

	writeBits(encodingMap.at(PSEUDO_EOF), output);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
	HuffmanNode const* current_node = encodingTree;

	bool bit = static_cast<bool>(input.readBit());

	while (!input.fail()) {
		if (current_node->isLeaf()) {
			int const character = current_node->character;

			if (character == PSEUDO_EOF) {
				break;
			}
			output.put(static_cast<char>(character));
			current_node = encodingTree;

		} else {
			current_node = bit ? current_node->one : current_node->zero;
			bit			 = static_cast<bool>(input.readBit());
		}
	}
}

void writeHeader(obitstream& output, map<int, int> const& frequencyTable) {
	stringstream header;
	header << '{';

	for (pair<int, int> const frequency : frequencyTable) {
		header << frequency.first << ':' << frequency.second << ',';
	}
	// Overwrite last ','
	header.seekp(-1, stringstream::cur);
	header << '}';

	output.write(header.str().c_str(), header.tellp());
}

void compress(istream& input, obitstream& output) {
	map<int, int> const frequencyTable = buildFrequencyTable(input);
	HuffmanNode* const encodingTree	   = buildEncodingTree(frequencyTable);
	map<int, string> const encodingMap = buildEncodingMap(encodingTree);
	freeTree(encodingTree);

	writeHeader(output, frequencyTable);
	input.clear();
	input.seekg(0, ios::beg);
	encodeData(input, encodingMap, output);
}

map<int, int> readHeader(ibitstream& input) {
	map<int, int> frequencyTable {};
	string character;
	string frequency;
	int byte = input.get();

	while (!input.fail() && byte != '}') {
		byte = input.get();

		while (!input.fail() && byte != ':') {
			character += to_string(asciiToDecimal(byte));
			byte = input.get();
		}

		byte = input.get();
		while (!input.fail() && byte != ',' && byte != '}') {
			frequency += to_string(asciiToDecimal(byte));
			byte = input.get();
		}

		frequencyTable[stoi(character)] = stoi(frequency);
		character.clear();
		frequency.clear();
	}

	return frequencyTable;
}

void decompress(ibitstream& input, ostream& output) {
	map<int, int> frequencyTable	= readHeader(input);
	HuffmanNode* const encodingTree = buildEncodingTree(frequencyTable);
	decodeData(input, encodingTree, output);
	freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
	if (node == nullptr) {
		return;
	}
	if (!node->isLeaf()) {
		freeTree(node->zero);
		freeTree(node->one);
	}
	delete node;
}
