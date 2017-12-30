/*
 * The Classifier class is like a handler for the whole program
 * It has perceptrons for its attribute, which it uses to predict class of given image.
 */

#ifndef Classifier_hpp
#define Classifier_hpp

#include <fstream>
#include <algorithm>
#include "Perceptron.hpp"

////////////////////////////////////////////////////
////////////////////Switch Below////////////////////
#define BIAS        0.0
#define EPOCH       5
#define SHUFFLE     false
#define RAND_WEIGHT false
////////////////////////////////////////////////////

class Classifier{
private:
    Perceptron* perceptron = NULL;
public:
    Classifier();
    ~Classifier();
    vector<Image*> parseImageFile(string imageFile, string labelFile) const;
    void train(vector<Image*> img);
    void testAndEvaluate(vector<Image*> img);
    int predict(int** feature) const;
    void shuffleImage(vector<Image*>& img);
};

#endif

