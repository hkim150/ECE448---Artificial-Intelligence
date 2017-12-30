#include "Classifier.hpp"

#define K   3

int main(){
    Classifier myClassifier;
    string trainingImage = "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/trainingimages";
    string trainingLabel = "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/traininglabels";
    string testImage = "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/testimages";
    string testLabel = "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.1/mp4.1.1/testlabels";
    
    //for(int K=1; K<10; K+=2){
        //cout << "K: " << K << endl;
        myClassifier.evaluate(trainingImage, trainingLabel, testImage, testLabel, K);
    //}
    
    return 0;
}
