#include "Classifier.hpp"

Classifier::Classifier(){
    srand((unsigned int)time(NULL));
    perceptrons = new Perceptron*[NUM_CLASS];
    for(int i=0; i<NUM_CLASS; i++){
        perceptrons[i] = new Perceptron(RAND_WEIGHT);
    }
}

Classifier::~Classifier(){
    if(perceptrons != NULL){delete[] perceptrons;}
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
            double** currFeature = img[j]->getFeature();
            int currClass = img[j]->getClass();
            int prediction = predict(currFeature);
            if(prediction != currClass){
                double alpha = 1.0/(double)(i*10+1.0);
                perceptrons[currClass]->updateWeight(currFeature, alpha);
                perceptrons[prediction]->updateWeight(currFeature, alpha*-1.0);
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
        double** currFeature = img[i]->getFeature();
        int currClass = img[i]->getClass();
        int prediction = predict(currFeature);
        if(prediction == currClass){correctCount++;}
        confusionMatrix[currClass][prediction]++;
    }
    cout << "Correctness: " << (double)correctCount/img.size() << endl << endl;
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
        cout << perceptrons[i]->getUpdateCount() << " updates" << endl << endl;
    }
}

int Classifier::predict(double** feature) const{
    int ret = 0;
    double max = 0, currVal = 0;
    for(int i=0; i<NUM_CLASS; i++){
        currVal = perceptrons[i]->getOutput(feature, BIAS);
        if(i == 0){max = currVal;}
        if(currVal > max){
            max = currVal;
            ret = i;
        }
    }
    return ret;
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

Perceptron** Classifier::getPerceptrons() const{return perceptrons;}

