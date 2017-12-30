#include "image.hpp"

void Image::printImage() const{
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            cout << pxl[i][j]->c;
        }
        cout << endl;
    }
}

Image& Image::operator=(const Image& other){
    if(this != &other){
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                Pixel* newPixel = new Pixel;
                newPixel->c = other.pxl[i][j]->c;
                newPixel->f = other.pxl[i][j]->f;
                this->pxl[i][j] = newPixel;
            }
        }
    }
    return *this;
}

Image::~Image(){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(pxl[i][j] != NULL){delete pxl[i][j];}
        }
    }
}
