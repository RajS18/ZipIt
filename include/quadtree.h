#ifndef QUADTREE_H
#define QUADTREE_H

#include <opencv2/opencv.hpp>


struct QuadtreeNode {
    bool isLeaf;
    cv::Scalar color;
    QuadtreeNode* children[4];

    QuadtreeNode() {
        isLeaf = false;
        for (int i = 0; i < 4; ++i)
            children[i] = nullptr;
    }
};

QuadtreeNode* createQuadtree(const cv::Mat& image, int depthThreshold, double colorThreshold);
void destroyQuadtree(QuadtreeNode* node);

#endif
