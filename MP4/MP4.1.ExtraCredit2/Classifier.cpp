#include "Classifier.hpp"

Classifier::Classifier(){
    srand((unsigned int)time(NULL));
    perceptron = new Perceptron(RAND_WEIGHT);
}

Classifier::~Classifier(){
    if(perceptron != NULL){delete perceptron;}
}

vector<Image*> Classifier::parseImageFile(string imageFile, string labelFile) const{
    ifstream myFile;
    vector<Image*> ret;
    
    myFile.open(imageFile);
    if(!myFile){
        cerr << "Unable to open the " << imageFile;
        cout << endl;
        return ret;
    }
    
    string line;
    vector<string> temp;
    
    while(getline(myFile, line)){
        if(line.size() == WIDTH){temp.push_back(line);}
        if(temp.size() == HEIGHT){
            Image* newImage = new Image(temp);
            ret.push_back(newImage);
            temp.clear();
        }
    }
    myFile.close();
    
    myFile.open(labelFile);
    if(!myFile){
        cerr << "Unable to open the " << labelFile;
        cout << endl;
        return ret;
    }
    
    int count = 0;
    while(getline(myFile, line)){
        if(!line.empty()){
            ret[count++]->setClass(line[0]);
        }
    }
    myFile.close();
    
    return ret;
}

void Classifier::train(vector<Image*> img){
    for(int i=0; i<EPOCH; i++){
        int correctCount = 0;
        if(SHUFFLE){shuffleImage(img);}
        for(int j=0; j<img.size(); j++){
            int** currFeature = img[j]->getFeature();
            int currClass = img[j]->getClass();
            int prediction = predict(currFeature);
            if(currClass < 0){currClass = -1;}
            if(prediction < 0){prediction = -1;}
            int y = currClass - prediction;
            if(prediction != currClass){
                double alpha = 1.0/(double)(i*10.0+1.0);
                perceptron->updateWeight(currFeature, y, alpha);
            }
            else{correctCount++;}
        }
        cout << "Epoch " << i+1 << ": " << (double)correctCount/img.size() << endl;
    }
}

void Classifier::testAndEvaluate(vector<Image*> img){
    cout << endl << "======= Testing Data =======" << endl;
    int correctCount = 0;
    double confusionMatrix[NUM_CLASS][NUM_CLASS] = {};
    for(int i=0; i<img.size(); i++){
        int** currFeature = img[i]->getFeature();
        int currClass = img[i]->getClass();
        int prediction = predict(currFeature);
        if(prediction == currClass){correctCount++;}
        confusionMatrix[currClass][prediction]++;
    }
    cout << "Correctness: " << (double)correctCount/img.size() << endl << endl;
    cout << perceptron->getUpdateCount() << " updates" << endl;
    for(int i=0; i<NUM_CLASS; i++){
        cout << "======= " << i << " =======" << endl;
        double sum = 0;
        for(int j=0; j<NUM_CLASS; j++){
            sum += confusionMatrix[i][j];
        }
        for(int j=0; j<NUM_CLASS; j++){
            confusionMatrix[i][j] /= sum;
            cout << j << ": " << confusionMatrix[i][j] << endl;
        }
    }
}

int Classifier::predict(int** feature) const{
    if(perceptron->getOutput(feature, BIAS) < 0.5){return 0;}
    else{return 1;}
}

void Classifier::shuffleImage(vector<Image*>& img){
    srand((unsigned int)time(NULL));
    int num1, num2;
    Image* temp;
    for(int i=0; i<img.size()*2; i++){
        num1 = rand()%img.size();
        num2 = rand()%img.size();
        temp = img[num1];
        img[num1] = img[num2];
        img[num2] = temp;
    }
}

