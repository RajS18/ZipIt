#include "quadtree.h"

QuadtreeNode* createQuadtree(const cv::Mat& image, int depthThreshold, double colorThreshold) {
    QuadtreeNode* node = new QuadtreeNode;

    if (depthThreshold <= 0 || colorThreshold <= 0.0 || image.cols <= 1 || image.rows <= 1) {
        node->isLeaf = true;
        node->color = mean(image);
    }
    else {
        Mat quadrant1 = image(Rect(0, 0, image.cols / 2, image.rows / 2));
        Mat quadrant2 = image(Rect(image.cols / 2, 0, image.cols / 2, image.rows / 2));
        Mat quadrant3 = image(Rect(0, image.rows / 2, image.cols / 2, image.rows / 2));
        Mat quadrant4 = image(Rect(image.cols / 2, image.rows / 2, image.cols / 2, image.rows / 2));

        node->children[0] = createQuadtree(quadrant1, depthThreshold - 1, colorThreshold);
        node->children[1] = createQuadtree(quadrant2, depthThreshold - 1, colorThreshold);
        node->children[2] = createQuadtree(quadrant3, depthThreshold - 1, colorThreshold);
        node->children[3] = createQuadtree(quadrant4, depthThreshold - 1, colorThreshold);
    }

    return node;
}

void destroyQuadtree(QuadtreeNode* node) {
    
     if (node != nullptr) {
        if (!node->isLeaf) {
            for (int i = 0; i < 4; ++i)
                destroyQuadtree(node->children[i]);
        }

        delete node;
    }
}
