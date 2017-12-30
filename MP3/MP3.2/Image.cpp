#include "Image.hpp"

Image::Image(vector<string> data){setGrid(data);}

bool Image::setGrid(vector<string> data){
    if(data.size() < HEIGHT){return false;}
    for(int i=0; i<HEIGHT; i++){
        if(data[i].size() < WIDTH){return false;}
        for(int j=0; j<WIDTH; j++){
            pixelGrid[i][j] = data[i][j];
        }
    }
    return true;
}

void Image::printImage() const{
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            cout << pixelGrid[i][j];
        }
        cout << endl;
    }
}

char Image::getPixel(int x, int y) const{return pixelGrid[x][y];}

Image& Image::operator=(const Image& other){
    if(this != &other){
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                this->pixelGrid[i][j] = other.pixelGrid[i][j];
            }
        }
    }
    return *this;
}
