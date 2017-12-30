#include "Bayes.hpp"

Bayes::Bayes(){
    for(int i=0; i<NUM_OF_DIGIT; i++){
        digitCount[i] = 0;
        maxAPosteriori[i] = 1;
        minAPosteriori[i] = 1;
    }
}

void Bayes::train(string fileName1, string fileName2, double laplace_k){
    parseImage(fileName1);
    parseDigit(fileName2);
    int fValCount[NUM_OF_DIGIT][HEIGHT][WIDTH] = {};
    for(int i=0; i<image.size(); i++){
        for(int j=0; j<HEIGHT; j++){
            for(int k=0; k<WIDTH; k++){
                if(image[i]->pxl[j][k]->f == 1){fValCount[digit[i]][j][k]++;}
            }
        }
    }
    for(int i=0; i<NUM_OF_DIGIT; i++){
        for(int j=0; j<HEIGHT; j++){
            for(int k=0; k<WIDTH; k++){
                p_f_given_digit[i][j][k] = (double)(fValCount[i][j][k] + laplace_k)/(double)(digitCount[i] + 2.0*laplace_k);
            }
        }
    }
}

void Bayes::test(string fileName1, string fileName2){
    parseImage(fileName1);
    parseDigit(fileName2);
    guess.clear();
    for(int i=0; i<image.size(); i++){
        guess.push_back(testImage(image[i]));
    }
}

int Bayes::testImage(Image* img){
    double temp;
    for(int i=0; i<NUM_OF_DIGIT; i++){
        p_digit_given_f[i] = log(p_digit[i]);
        for(int j=0; j<HEIGHT; j++){
            for(int k=0; k<WIDTH; k++){
                temp = p_f_given_digit[i][j][k];
                if(img->pxl[j][k]->f == 0){temp = 1 - temp;}
                p_digit_given_f[i] += log(temp);
            }
        }
        if(maxAPosteriori[i] == 1 || maxAPosteriori[i] < p_digit_given_f[i]){
            maxAPosteriori[i] = p_digit_given_f[i];
            Image* newImage = new Image;
            newImage->operator=(*img);
            mostPrototypicalImage[i] = newImage;
        }
        if(minAPosteriori[i] == 1 || minAPosteriori[i] > p_digit_given_f[i]){
            minAPosteriori[i] = p_digit_given_f[i];
            Image* newImage = new Image;
            newImage->operator=(*img);
            leastPrototypicalImage[i] = newImage;
        }
    }
    
    int ret = 0;
    double maxEncountered = 1;
    for(int i=0; i<NUM_OF_DIGIT; i++){
        if(maxEncountered == 1 || p_digit_given_f[i] > maxEncountered){
            maxEncountered = p_digit_given_f[i];
            ret = i;
        }
    }
    return ret;
}

void Bayes::evaluate(){
    int correctCount = 0;
    int confusionMatrixCount[NUM_OF_DIGIT][NUM_OF_DIGIT] = {};
    vector<pair<int, double>> highestConfusionRate;
    
    for(int i=0; i<digit.size(); i++){
        if(digit[i] == guess[i]){correctCount++;}
        confusionMatrixCount[digit[i]][guess[i]]++;
    }
    cout << "Correctness: " << (double)correctCount/digit.size() << endl << endl;
    
    for(int i=0; i<NUM_OF_DIGIT; i++){
        cout << "=== " << i << " ===" << endl;
        for(int j=0; j<NUM_OF_DIGIT; j++){
            confusionMatrix[i][j] = (double)confusionMatrixCount[i][j]/digitCount[i];
            cout << j << ": " << confusionMatrix[i][j] << endl;
        }
        cout << endl;
    }
    
    for(int i=0; i<NUM_OF_DIGIT; i++){
        cout << "Most prototypical Image of " << i << ": " << endl;
        mostPrototypicalImage[i]->printImage();
        
        cout << "Least prototypical Image of " << i << ": " << endl;
        leastPrototypicalImage[i]->printImage();
    }
    
    for(int i=0; i<NUM_OF_DIGIT; i++){
        int size = (int)highestConfusionRate.size();
        pair<int, double> newPair = pair<int, double>(i, confusionMatrix[i][i]);
        if(size == 0){highestConfusionRate.push_back(newPair);}
        else{
            for(int j=0; j<size; j++){
                if(newPair.second < highestConfusionRate[j].second){
                    highestConfusionRate.insert(highestConfusionRate.begin()+j, newPair);
                    break;
                }
                if(j == size-1){highestConfusionRate.push_back(newPair);}
            }
        }
    }
    
    vector<pair<int, double>> confusedWith;
    int currDigit, maxDigit = -1;
    double maxRatio = -1.0;
    for(int i=0; i<4; i++){
        currDigit = highestConfusionRate[i].first;
        maxDigit = -1;
        maxRatio = -1.0;
        for(int j=0; j<NUM_OF_DIGIT; j++){
            if(j != currDigit && confusionMatrix[currDigit][j] > maxRatio){
                maxRatio = confusionMatrix[currDigit][j];
                maxDigit = j;
            }
        }
        confusedWith.push_back(pair<int, double>(maxDigit, maxRatio));
    }
    
    cout << "Four digits with highest confusion rates:" << endl;
    for(int i=0; i<4; i++){
        cout << highestConfusionRate[i].first << ": " << highestConfusionRate[i].second;
        cout << ", Most confused with " << confusedWith[i].first << ": " << confusedWith[i].second << endl;
    }
    cout << endl;
    
    for(int i=0; i<confusedWith.size(); i++){
        printOddRatio(highestConfusionRate[i].first, confusedWith[i].first);
        cout << endl;
    }
}

void Bayes::printLikelihood(int c) const{
    double likelihood;
    cout << "Likelihood of " << c << ": " << endl;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            likelihood = log(p_f_given_digit[c][i][j]);
            if(likelihood > -0.75){cout << '+';}
            else if(likelihood < -6){cout << '-';}
            else{cout << ' ';}
        }
        cout << endl;
    }
    cout << endl;
}

void Bayes::printOddRatio(int c1, int c2){
    double oddRatio;
    printLikelihood(c1);
    printLikelihood(c2);
    
    cout << "Odd ratio of " << c1 << " over " << c2 << ":" << endl;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            oddRatio = log(p_f_given_digit[c1][i][j]/p_f_given_digit[c2][i][j]);
            if(abs(oddRatio) < 0.2){cout << ' ';}
            else{
                if(oddRatio > 0){cout << '+';}
                else{cout << '-';}
            }
        }
        cout << endl;
    }
}

bool Bayes::parseImage(string fileName){
    ifstream myFile;
    myFile.open(fileName);
    
    if(!myFile){
        cerr << "Unable to open the file";
        cout << endl;
        return false;
    }
    
    string line;
    vector<string> temp;
    image.clear();
    
    while(getline(myFile, line)){
        temp.push_back(line);
        if(temp.size() == HEIGHT){
            Image* newImage = new Image;
            for(int i=0; i<temp.size(); i++){
                for(int j=0; j<temp[i].size(); j++){
                    Pixel* newPixel = new Pixel;
                    newPixel->c = temp[i][j];
                    if(temp[i][j] == ' '){newPixel->f = 0;}
                    else{newPixel->f = 1;}
                    newImage->pxl[i][j] = newPixel;
                }
            }
            image.push_back(newImage);
            temp.clear();
        }
    }
    return true;
}

bool Bayes::parseDigit(string fileName){
    ifstream myFile;
    myFile.open(fileName);
    
    if(!myFile){
        cerr << "Unable to open the file";
        cout << endl;
        return false;
    }
    
    int num;
    string line;
    digit.clear();
    for(int i=0; i<NUM_OF_DIGIT; i++){digitCount[i] = 0;}
    
    while(getline(myFile, line)){
        num = line[0] - 48;
        if(num>=0 && num<=9){
            digit.push_back(num);
            digitCount[num]++;
        }
    }
    
    for(int i=0; i<NUM_OF_DIGIT; i++){
        p_digit[i] = (double)digitCount[i]/(double)digit.size();
    }
    
    return true;
}
