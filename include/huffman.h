#include <map>
#include <iostream>
using namespace std;
#ifndef HUFFMAN_H
#define HUFFMAN_H

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
};

struct FrequencyComparator {
    bool operator()(HuffmanNode* a, HuffmanNode* b) const {
        return a->frequency > b->frequency;
    }
};

map<char, string> huffmanCodeMap;
void generateHuffmanCodes(HuffmanNode* root, const string& currentCode);
HuffmanNode* buildHuffmanTree(const map<char, int>& frequencyMap);

#endif // HUFFMAN_H
