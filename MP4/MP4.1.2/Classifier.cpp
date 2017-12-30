#include "Classifier.hpp"

void Classifier::evaluate(string trainingImage, string trainingLabel, string testImage, string testLabel, int k) const{
    vector<Image*> imagePool, testImagePool;
    imagePool = parseImageFile(trainingImage, trainingLabel);
    testImagePool = parseImageFile(testImage, testLabel);
    
    int correctCount = 0;
    time_t timeStart, timeEnd;
    
    timeStart = clock();
    for(int i=0; i<testImagePool.size(); i++){
        int answer = testImagePool[i]->getClass();
        int prediction = classify(imagePool, testImagePool[i], k);
        if(answer == prediction){correctCount++;}
    }
    timeEnd = clock();
    
    cout << "Accuracy: " << (double)correctCount/testImagePool.size() << endl;
    cout << "Execution Time: " << (double)(timeEnd - timeStart)/CLOCKS_PER_SEC << " sec" << endl;
}

int Classifier::classify(vector<Image*> imagePool, Image* testImage, int k) const{
    return getMostLikelyClass(getKNearestNeighbor(imagePool, testImage, k));
}

int Classifier::getMostLikelyClass(vector<Image*> img) const{
    int ret = -1, max = -1;
    int frequency[NUM_CLASS] = {};
    for(int i=0; i<img.size(); i++){frequency[img[i]->getClass()]++;}
    for(int i=0; i<NUM_CLASS; i++){
        if(frequency[i] > max){
            max = frequency[i];
            ret = i;
        }
    }
    return ret;
}

vector<Image*> Classifier::getKNearestNeighbor(vector<Image*> imagePool, Image* testImage, int k) const{
    typedef struct imageDistancePair{
        Image* img;
        int distance;
    } IDP;
    vector<IDP*> KNearest;
    for(int i=0; i<k; i++){
        IDP* newIDP = new IDP;
        newIDP->img = NULL;
        newIDP->distance = -1;
        KNearest.push_back(newIDP);
    }
    for(int i=0; i<imagePool.size(); i++){
        double dist = getDistance(imagePool[i], testImage);
        int j=k;
        while(dist < KNearest[j-1]->distance || KNearest[j-1]->distance < 0){
            j--;
            if(j == 0){break;}
        }
        if(j < k){
            IDP* newIDP = new IDP;
            newIDP->img = imagePool[i];
            newIDP->distance = dist;
            KNearest.insert(KNearest.begin()+j, newIDP);
            delete KNearest[k];
            KNearest.pop_back();
        }
    }
    vector<Image*> ret;
    for(int i=0; i<k; i++){
        ret.push_back(KNearest[i]->img);
        delete KNearest[i];
    }
    return ret;
}

double Classifier::getDistance(Image* img1, Image* img2) const{
    int ret = 0;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(img1->getFeatureAt(i, j) != img2->getFeatureAt(i, j)){ret++;}
        }
    }
    return ret;
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
