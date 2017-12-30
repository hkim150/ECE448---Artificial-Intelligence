#include "Bayes.hpp"

bool Bayes::computeLikelihood(double laplace_smoothing_k){
    vector<Image>* container[CLASSIFY] = {&yesImage, &noImage};
    for(int c=0; c<CLASSIFY; c++){if(container[c]->empty()){return false;}}
    
    for(int c=0; c<CLASSIFY; c++){
        for(int d=0; d<container[c]->size(); d++){
            for(int i=0; i<HEIGHT; i++){
                for(int j=0; j<WIDTH; j++){
                    if(container[c]->at(d).getPixel(i,j) == HIGH){likelihood[c][i][j]++;}
                }
            }
        }
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                likelihood[c][i][j] = (likelihood[c][i][j] + laplace_smoothing_k)/(container[c]->size() + 2.0 * laplace_smoothing_k);
            }
        }
    }
    return true;
}

bool Bayes::testImages(){
    if(isImageEmpty()){return false;}
    vector<Image>* container[CLASSIFY] = {&yesImage, &noImage};
    bool correct[CLASSIFY] = {true, false};
    for(int k=0; k<CLASSIFY; k++){
        for(int i=0; i<container[k]->size(); i++){
            if(guessClass(container[k]->at(i)) == correct[k]){correctCount[k]++;}
        }
    }
    return true;
}

void Bayes::evaluate(){
    vector<Image>* container[CLASSIFY] = {&yesImage, &noImage};
    int totCorrect = 0, totTest = 0;
    for(int i=0; i<CLASSIFY; i++){
        totCorrect += correctCount[i];
        totTest += container[i]->size();
    }
    cout << "Correctness: " << (double)totCorrect/totTest << endl << endl;
    
    cout << "Confusion Matrix:" << endl << "\t\t" << "Yes" << "\t\t" << "No" << endl;
    for(int i=0; i<CLASSIFY; i++){
        if(i == 0){cout << "Yes:" << '\t';}
        else{cout << "No:" << "\t\t";}
        for(int j=0; j<CLASSIFY; j++){
            if(i == j){confusionMatrix[i][j] = (double)correctCount[i]/container[i]->size();}
            else{confusionMatrix[i][j] = 1.0 - (double)correctCount[i]/container[i]->size();}
            cout << confusionMatrix[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

bool Bayes::computePClass(){
    if(isImageEmpty()){return false;}
    vector<Image>* container[CLASSIFY] = {&yesImage, &noImage};
    double sum = 0;
    for(int i=0; i<CLASSIFY; i++){sum += container[i]->size();}
    for(int i=0; i<CLASSIFY; i++){p_class[i] = (double)container[i]->size()/sum;}
    return true;
}

bool Bayes::guessClass(Image img){
    double maximumAPosteriori[CLASSIFY];
    for(int k=0; k<CLASSIFY; k++){
        maximumAPosteriori[k] = log(p_class[k]);
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                if(img.getPixel(i, j) == HIGH){maximumAPosteriori[k] += log(likelihood[k][i][j]);}
                else{maximumAPosteriori[k] += log(1 - likelihood[k][i][j]);}
            }
        }
    }
    return maximumAPosteriori[0] > maximumAPosteriori[1];
}

bool Bayes::isImageEmpty() const{
    const vector<Image>* container[CLASSIFY] = {&yesImage, &noImage};
    for(int i=0; i<CLASSIFY; i++){if(container[i]->empty()){return true;}}
    return false;
}

bool Bayes::parseImage(string fileName, bool yesOrNo){
    ifstream myFile;
    myFile.open(fileName);
    
    if(!myFile){
        cerr << "Unable to open the file";
        cout << endl;
        return false;
    }
    
    vector<Image>* imageContainer;
    if(yesOrNo){imageContainer = &yesImage;}
    else{imageContainer = &noImage;}
    imageContainer->clear();
    
    string line;
    vector<string> temp;

    while(getline(myFile, line)){
        if(line.size() == WIDTH){temp.push_back(line);}
        if(temp.size() == HEIGHT){
            Image newImage(temp);
            imageContainer->push_back(newImage);
            temp.clear();
        }
    }
    myFile.close();
    return true;
}
