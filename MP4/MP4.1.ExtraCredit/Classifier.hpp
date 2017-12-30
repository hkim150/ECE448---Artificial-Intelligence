#ifndef Classifier_hpp
#define Classifier_hpp

#include <fstream>
#include <algorithm>
#include "Perceptron.hpp"

#define BIAS            0.0
#define EPOCH           5
#define SHUFFLE         true
#define RAND_WEIGHT     true

class Classifier{
private:
    Perceptron** perceptrons = NULL;
public:
    Classifier();
    ~Classifier();
    vector<Image*> parseImageFile(string imageFile, string labelFile) const;
    void train(vector<Image*> img);
    void testAndEvaluate(vector<Image*> img);
    int predict(double** feature) const;
    void shuffleImage(vector<Image*>& img);
    Perceptron** getPerceptrons() const;
};

#endif

