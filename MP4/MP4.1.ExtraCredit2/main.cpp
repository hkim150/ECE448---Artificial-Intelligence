#include "Classifier.hpp"

int main(){
    Classifier c;
    
    vector<Image*> img1, img2;
    img1 = c.parseImageFile("/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.ExtraCredit2/mp4.1.ExtraCredit2/facedatatrain.txt", "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.ExtraCredit2/mp4.1.ExtraCredit2/facedatatrainlabels.txt");
    img2 = c.parseImageFile("/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.ExtraCredit2/mp4.1.ExtraCredit2/facedatatest.txt", "/Users/HyunBinKim/Downloads/Courses/ece448/Fa17/mp4/mp4.1.ExtraCredit2/mp4.1.ExtraCredit2/facedatatestlabels.txt");
    
    c.train(img1);
    c.testAndEvaluate(img2);
    
    return 0;
}

