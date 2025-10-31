//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"

using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

// Converts text in input.txt to a binary code
// Text characters are assigned bit strings as codes
// Stores nodes in parallel arrays, including index arrays for the encoding structure (binary tree -> left and right arrays)
// String lengths are based on character frequency to minimize length
int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
// Uses a given algorithm to create a binary encoding tree in parallel arrays
// Each node (stored as parallel array values) has a left and right int that it uses as an index to its children
// The given algorithm assigns leaf nodes and creates parents to connect them, using int `nextFree` to index new nodes
// The final tree's leaf nodes' depths are inversely proportional to their character's frequency (the goal of the algorithm)
// Uses a MinHeap object to create the encoding tree
int buildEncodingTree(int nextFree) {
    MinHeap heap;
    for (int i = 0; i < nextFree; ++i)
        heap.push(i, weightArr);
    while (heap.size > 1) {
        int firstMin = heap.pop(weightArr);
        int secondMin = heap.pop(weightArr);

        charArr[nextFree] = '_';
        weightArr[nextFree] = weightArr[firstMin] + weightArr[secondMin];
        leftArr[nextFree] = firstMin;
        rightArr[nextFree] = secondMin;

        heap.push(nextFree, weightArr);
        nextFree++;
    }
    int root = heap.pop(weightArr);
    return root;
}

// Step 4: Use an STL stack to generate codes
// Given int `root`, the root of a binary tree stored in parallel arrays, generates binary codes representing leaf positions
// Each left edge from the root to a leaf adds a '1' to the string, while each right edge adds a '0'
// The final code represents a node's position; a code's length is equal to its node's depth in the tree
// Codes are stored in string[] `codes[]`
// Uses a stack object to traverse the encoding tree
void generateCodes(int root, string codes[]) {
    if (leftArr[root] == -1 && rightArr[root] == -1) {
        int charIdx = charArr[root] - 'a';
        codes[charIdx] = "0";
        return;
    }
    stack<pair<int, string>> s;
    s.push({root, ""});
    while (!s.empty()) {
        int node = s.top().first;
        string code = s.top().second;
        s.pop();

        if (leftArr[node] == -1 && rightArr[node] == -1) { // node is a leaf
            int charIdx = charArr[node] - 'a';
            codes[charIdx] = code;
        }
        else {
            if (leftArr[node] != -1) // node has a left child
                s.push({leftArr[node], code + "0"});
            if (rightArr[node] != -1) // node has a right child
                s.push({rightArr[node], code + "1"});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}