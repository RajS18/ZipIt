#include "compress.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: CompressionEngine <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::string fileExtension = inputFile.substr(inputFile.find_last_of('.') + 1);
    transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

    if (fileExtension == "txt") {
        compressWithHuffman(inputFile, outputFile);
    }
    else if (fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png") {
        compressWithQuadtree(inputFile, outputFile, 5, 30.0);
    }
    else {
        std::cout << "Unsupported file format!" << std::endl;
    }

    return 0;
}
