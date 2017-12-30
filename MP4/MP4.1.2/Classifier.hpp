/*
 * The Classifier class is like a handler for the whole program
 * It uses the K Nearest Neighbor method to classify an image
 */

#ifndef Classifier_hpp
#define Classifier_hpp

#include <fstream>
#include "Image.hpp"

class Classifier{
public:
    vector<Image*> parseImageFile(string imageFile, string labelFile) const;
    double getDistance(Image* img1, Image* img2) const;
    vector<Image*> getKNearestNeighbor(vector<Image*> imagePool, Image* testImage, int k) const;
    int getMostLikelyClass(vector<Image*> img) const;
    int classify(vector<Image*> imagePool, Image* testImage, int k) const;
    void evaluate(string trainingImage, string trainingLabel, string testImage, string testLabel, int k) const;
};

#endif
