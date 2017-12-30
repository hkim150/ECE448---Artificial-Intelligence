#ifndef Bayes_hpp
#define Bayes_hpp

#include <fstream>
#include "Image.hpp"

class Bayes{
private:
    vector<Image> image;                                // vector for holding parsed images
    vector<int> guess;                                  // vector of guesses of images
    int classCount[NUM_CLASS] = {};                     // holds the number of each classes
    double*** p_of_g_given_class = NULL;                // p(g|class) holder
    double p_class[NUM_CLASS] = {};                     // p(class) holder
    double confusionMatrix[NUM_CLASS][NUM_CLASS] = {};  // confusion matrix holder
public:
    bool parseImage(string imageFileName, string labelFileName);    // parses both data and label file
    void train(double laplace_k);
    void test();
    void evaluate();
    ~Bayes();                                           // destructor for freeing heap
};

#endif
