#include "Classifier.hpp"

int main(){
    Classifier c;
    
    vector<Image*> img1, img2;
    img1 = c.parseImageFile("/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/trainingimages", "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/traininglabels");
    img2 = c.parseImageFile("/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/testimages", "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/testlabels");
    
    c.train(img1);
    Perceptron** p = c.getPerceptrons();
    for(int i=0; i<NUM_CLASS; i++){
        p[i]->printWeight();
        cout << endl;
    }
    c.testAndEvaluate(img2);
    
    return 0;
}

