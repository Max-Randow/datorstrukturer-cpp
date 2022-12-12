// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"

#include <queue>

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

void writeBits(string const& input, obitstream& output) {
	for (char const bit : input) {
		// Convert letter to ascii.
		output.writeBit(bit - '0');
	}
}

void encodeData(istream& input,
				const map<int, string>& encodingMap,
				obitstream& output) {
	int character = input.get();

	while (!input.fail()) {
		writeBits(encodingMap.at(character), output);
		character = input.get();
	}

	writeBits(encodingMap.at(PSEUDO_EOF), output);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
	// Läs bitar från input och traversera trädet för att hitta bokstäverna.
	// Dvs anta att träd parametern är redan återskapad från filen.
}

void compress(istream& input, obitstream& output) {
	// TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
	// TODO: implement this function
}

void freeTree(HuffmanNode* node) {
	if (!node->isLeaf()) {
		freeTree(node->zero);
		freeTree(node->one);
	}
	delete node;
}
