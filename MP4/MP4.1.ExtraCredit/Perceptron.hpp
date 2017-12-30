#ifndef Perceptron_hpp
#define Perceptron_hpp

#include <cmath>
#include "Image.hpp"

class Perceptron{
private:
    double* weight = NULL;
    int updateCount = 0;
    int signFunc(double input) const;
    double sigmoidFunc(double input) const;
public:
    Perceptron(bool rand_weight);
    ~Perceptron();
    int getUpdateCount() const;
    double getOutput(double** feature, double bias) const;
    void updateWeight(double** feature, double alpha);
    void printWeight() const;
};

#endif

