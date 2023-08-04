#ifndef COMPRESS_H
#define COMPRESS_H

void compressWithHuffman(const std::string& inputFile, const std::string& outputFile);
void compressWithLWZ(const std::string& inputFile, const std::string& outputFile);
void compressWithQuadtree(const std::string& inputFile, const std::string& outputFile, int depthThreshold, double colorThreshold);

#endif
