#include "Image.hpp"

Image::Image(){makeNewFeatureSpace();}

Image::Image(vector<string> data){
    feature = new int*[HEIGHT];
    for(int i=0; i<HEIGHT; i++){
        feature[i] = new int[WIDTH];
        for(int j=0; j<WIDTH; j++){
            if(data[i][j] == WHITE){feature[i][j] = 0;}
            else{feature[i][j] = 1;}
        }
    }
}

void Image::makeNewFeatureSpace(){
    feature = new int*[HEIGHT];
    for(int i=0; i<HEIGHT; i++){
        feature[i] = new int[WIDTH];
        for(int j=0; j<WIDTH; j++){feature[i][j] = 0;}
    }
}

void Image::printFeature() const{
    if(feature != NULL){
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                cout << feature[i][j];
            }
            cout << endl;
        }
    }
    else{cout << "no feature" << endl;}
}

int** Image::getFeature(){return feature;}

int Image::getFeatureAt(int x, int y) const{return feature[x][y];}

int Image::getClass() const{return classify;}

void Image::setClass(char num){classify = (int)num - 48;}

Image& Image::operator=(const Image& other){
    if(this != &other){
        if(this->feature == NULL){this->makeNewFeatureSpace();}
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                this->feature[i][j] = other.feature[i][j];
            }
        }
    }
    return *this;
}

void Image::deleteFeature(){
    if(feature != NULL){
        for(int i=0; i<HEIGHT; i++){
            if(feature[i] != NULL){delete[] feature[i];}
        }
        delete[] feature;
        feature = NULL;
    }
}

Image::~Image(){deleteFeature();}


