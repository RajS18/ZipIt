#include "huffman.h"
HuffmanNode* buildHuffmanTree(const map<char, int>& frequencyMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, FrequencyComparator> pq;

    for (const auto& pair : frequencyMap) {
        HuffmanNode* node = new HuffmanNode;
        node->data = pair.first;
        node->frequency = pair.second;
        node->left = nullptr;
        node->right = nullptr;
        pq.push(node);
    }

    while (pq.size() > 1) {
        HuffmanNode* leftChild = pq.top();
        pq.pop();

        HuffmanNode* rightChild = pq.top();
        pq.pop();

        HuffmanNode* parentNode = new HuffmanNode;
        parentNode->data = '\0';
        parentNode->frequency = leftChild->frequency + rightChild->frequency;
        parentNode->left = leftChild;
        parentNode->right = rightChild;

        pq.push(parentNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, const string& currentCode) {
    if (root == nullptr)
        return;

    if (root->data != '\0')
        huffmanCodeMap[root->data] = currentCode;

    generateHuffmanCodes(root->left, currentCode + "0");
    generateHuffmanCodes(root->right, currentCode + "1");
}
