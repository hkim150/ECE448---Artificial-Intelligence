#ifndef Bayes_hpp
#define Bayes_hpp

#include <cmath>
#include <fstream>

#include "Image.hpp"

#define CLASSIFY    2
#define HIGH        ' '
#define LOW         '%'

class Bayes{
private:
    vector<Image> yesImage, noImage;
    int correctCount[CLASSIFY] = {};
    double likelihood[CLASSIFY][HEIGHT][WIDTH] = {};
    double p_class[CLASSIFY] = {};
    double confusionMatrix[CLASSIFY][CLASSIFY] = {};
public:
    bool testImages();
    void evaluate();
    bool computeLikelihood(double laplace_smoothing_k);
    bool computePClass();
    bool guessClass(Image img);
    bool isImageEmpty() const;
    bool parseImage(string filename, bool yesOrNo);
};

#endif
