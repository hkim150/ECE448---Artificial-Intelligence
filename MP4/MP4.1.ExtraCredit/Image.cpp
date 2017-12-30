#include "Image.hpp"

Image::Image(){makeNewFeatureSpace();}

Image::Image(vector<string> data){
    feature = new double*[HEIGHT];
    for(int i=0; i<HEIGHT; i++){
        feature[i] = new double[WIDTH];
        for(int j=0; j<WIDTH; j++){
            if(NUM_PIXEL_VAL  == 2){
                if(data[i][j] == WHITE){feature[i][j] = 0.0;}
                else{feature[i][j] = 1.0;}
            }
            else if(NUM_PIXEL_VAL == 3){
                if(data[i][j] == WHITE){feature[i][j] = 0.0;}
                else if(data[i][j] == GRAY){feature[i][j] = 0.5;}
                else{feature[i][j] = 1.0;}
            }
        }
    }
}

void Image::makeNewFeatureSpace(){
    feature = new double*[HEIGHT];
    for(int i=0; i<HEIGHT; i++){
        feature[i] = new double[WIDTH];
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

double** Image::getFeature(){return feature;}

double Image::getFeatureAt(int x, int y) const{return feature[x][y];}

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


