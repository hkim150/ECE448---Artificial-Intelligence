#include "Bayes.hpp"

void Bayes::train(double laplace_k){
    int sum = 0;
    for(int i=0; i<NUM_CLASS; i++){sum += classCount[i];}
    for(int i=0; i<NUM_CLASS; i++){p_class[i] = (double)classCount[i]/sum;}
    
    int patchCount;
    if(METHOD){patchCount = NUM_DSJNT_PATCH;}
    else{patchCount = NUM_OVRLP_PATCH;}
    
    p_of_g_given_class = new double** [NUM_CLASS];
    for(int i=0; i<NUM_CLASS; i++){
        p_of_g_given_class[i] = new double* [patchCount];
        for(int j=0; j<patchCount; j++){
            p_of_g_given_class[i][j] = new double [NUM_FEAT_VAL];
            for(int k=0; k<NUM_FEAT_VAL; k++){
                p_of_g_given_class[i][j][k] = laplace_k;
            }
        }
    }
    
    for(int i=0; i<image.size(); i++){
        vector<int> patches;
        if(METHOD){patches = image[i].getDisjointPatchValue();}
        else{patches = image[i].getOverlapPatchValue();}
        for(int j=0; j<patches.size(); j++){
            p_of_g_given_class[image[i].getClass()][j][patches[j]]++;
        }
    }
    
    for(int i=0; i<NUM_CLASS; i++){
        for(int j=0; j<patchCount; j++){
            for(int k=0; k<NUM_FEAT_VAL; k++){
                p_of_g_given_class[i][j][k] = p_of_g_given_class[i][j][k] / (classCount[i] + NUM_FEAT_VAL * laplace_k);
            }
        }
    }
}

void Bayes::test(){
    int num;
    for(int i=0; i<image.size(); i++){
        vector<int> patches;
        if(METHOD){patches = image[i].getDisjointPatchValue();}
        else{patches = image[i].getOverlapPatchValue();}
        
        num = -1;
        double aPosteriori, maximumAPosteriori = 0;
        for(int j=0; j<NUM_CLASS; j++){
            aPosteriori = log(p_class[i]);
            for(int k=0; k<patches.size(); k++){
                aPosteriori += log(p_of_g_given_class[j][k][patches[k]]);
            }
            if(maximumAPosteriori == 0 || aPosteriori > maximumAPosteriori){
                maximumAPosteriori = aPosteriori;
                num = j;
            }
        }
        guess.push_back(num);
    }
}

void Bayes::evaluate(){
    int correctCount = 0;
    int confusionMatrixCount[NUM_CLASS][NUM_CLASS] = {};
    
    for(int i=0; i<image.size(); i++){
        confusionMatrixCount[image[i].getClass()][guess[i]]++;
        if(guess[i] == image[i].getClass()){correctCount++;}
    }
    cout << "Correctness: " << (double)correctCount/image.size() << endl << endl;

    for(int i=0; i<NUM_CLASS; i++){
        cout << "=== " << i << " ===" << endl;
        for(int j=0; j<NUM_CLASS; j++){
            confusionMatrix[i][j] = (double)confusionMatrixCount[i][j]/classCount[i];
            cout << j << ": " << confusionMatrix[i][j] << endl;
        }
        cout << endl;
    }
}

bool Bayes::parseImage(string imageFileName, string labelFileName){
    ifstream myFile;
    myFile.open(imageFileName);
    if(!myFile){
        cerr << "Unable to open the " << imageFileName;
        cout << endl;
        return false;
    }
    image.clear();
    
    string line;
    vector<string> temp;
    
    while(getline(myFile, line)){
        if(line.size() == WIDTH){temp.push_back(line);}
        if(temp.size() == HEIGHT){
            Image newImage(temp);
            image.push_back(newImage);
            temp.clear();
        }
    }
    myFile.close();
    
    myFile.open(labelFileName);
    if(!myFile){
        cerr << "Unable to open the " << labelFileName;
        cout << endl;
        return false;
    }
    
    int count = 0;
    for(int i=0; i<NUM_CLASS; i++){classCount[i] = 0;}
    while(getline(myFile, line)){
        if(!line.empty()){
            classCount[(int)line[0] - 48]++;
            image[count++].setClass(line[0]);
        }
    }
    myFile.close();
    
    return true;
}

Bayes::~Bayes(){
    int patchCount;
    if(METHOD){patchCount = NUM_DSJNT_PATCH;}
    else{patchCount = NUM_OVRLP_PATCH;}
    if(p_of_g_given_class != NULL){
        for(int i=0; i<NUM_CLASS; i++){
            for(int j=0; j<patchCount; j++){
                delete[] p_of_g_given_class[i][j];
            }
            delete[] p_of_g_given_class[i];
        }
        delete p_of_g_given_class;
    }
}

