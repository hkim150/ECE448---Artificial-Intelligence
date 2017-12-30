/*
 * The Perceptron class takes in feature values and outputs
 * either sign or sigmoid function of the computed value.
 * Which the classifier then predicts the class with the output.
 * updateWeight is used only during training.
 */

#ifndef Perceptron_hpp
#define Perceptron_hpp

#include "Image.hpp"

class Perceptron{
private:
    double* weight = NULL;
    int updateCount = 0;
    int signFunc(double input) const;
public:
    Perceptron(bool rand_weight);
    ~Perceptron();
    int getUpdateCount() const;
    double getOutput(int** feature, double bias) const;
    void updateWeight(int** feature, double alpha);
};

#endif
