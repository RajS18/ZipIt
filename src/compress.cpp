#include "compress.h"
#include "huffman.h"
#include "lwz.h"
#include "quadtree.h"
#include <iostream>
using namespace std;

void compressWithHuffman(const std::string& inputFile, const std::string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Failed to open file!" << endl;
        return;
    }

    map<char, int> frequencyMap;
    char ch;

    while (inFile.get(ch))
        frequencyMap[ch]++;

    inFile.clear();
    inFile.seekg(0, ios::beg);

    HuffmanNode* root = buildHuffmanTree(frequencyMap);
    generateHuffmanCodes(root, "");

    string encodedData = "";

    while (inFile.get(ch))
        encodedData += huffmanCodeMap[ch];

    int paddingBits = 8 - (encodedData.length() % 8);
    encodedData += string(paddingBits, '0');

    outFile << paddingBits << " ";

    for (size_t i = 0; i < encodedData.length(); i += 8) {
        string byteStr = encodedData.substr(i, 8);
        char byte = static_cast<char>(stoi(byteStr, nullptr, 2));
        outFile.put(byte);
    }

    inFile.close();
    outFile.close();

    cout << "File compressed with Huffman encoding!" << endl;
}

void compressWithLWZ(const std::string& inputFile, const std::string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Failed to open file!" << endl;
        return;
    }

    initializeLWZCodeMap();

    string currentString = "";
    string compressedData = "";

    char ch;
    while (inFile.get(ch)) {
        string currentStringPlusCh = currentString + ch;

        if (lwzCodeMap.count(currentStringPlusCh)) {
            currentString = currentStringPlusCh;
        }
        else {
            compressedData += to_string(lwzCodeMap[currentString]) + " ";
            lwzCodeMap[currentStringPlusCh] = lwzCodeMap.size();
            currentString = string(1, ch);
        }
    }

    if (!currentString.empty())
        compressedData += to_string(lwzCodeMap[currentString]) + " ";

    outFile << compressedData;

    inFile.close();
    outFile.close();

    cout << "File compressed with LWZ encoding!" << endl;
}

void compressWithQuadtree(const std::string& inputFile, const std::string& outputFile, int depthThreshold, double colorThreshold) {
    cv::Mat image = cv::imread(inputFile);

    if (image.empty()) {
        std::cerr << "Failed to open image!" << std::endl;
        return;
    }

    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    std::vector<QuadtreeNode*> roots(channels.size());

    for (size_t i = 0; i < channels.size(); ++i)
        roots[i] = createQuadtree(channels[i], depthThreshold, colorThreshold);

    for (size_t i = 0; i < channels.size(); ++i)
        destroyQuadtree(roots[i]);

    std::cout << "Image compressed with Quadtree fractal compression!" << std::endl;
}
