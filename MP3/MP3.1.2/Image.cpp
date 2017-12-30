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

int Image::getClass() const{return classify;}

void Image::setClass(char num){classify = (int)num - 48;}

vector<int> Image::getDisjointPatchValue(){
    vector<int> ret;
    for(int i=0; i<HEIGHT; i+=PATCH_HEIGHT){
        for(int j=0; j<WIDTH; j+=PATCH_WIDTH){
            ret.push_back(getPatchValue(j, i));
        }
    }
    return ret;
}

vector<int> Image::getOverlapPatchValue(){
    vector<int> ret;
    for(int i=0; i<HEIGHT-PATCH_HEIGHT+1; i++){
        for(int j=0; j<WIDTH-PATCH_WIDTH+1; j++){
            ret.push_back(getPatchValue(j, i));
        }
    }
    return ret;
}

int Image::getPatchValue(int x, int y) const{
    int ret = 0;
    for(int i=0; i<PATCH_HEIGHT; i++){
        for(int j=0; j<PATCH_WIDTH; j++){
            if(NUM_PIXEL_VAL == 2){
                if(pixelGrid[y+i][x+j] != WHITE){ret += pow(NUM_PIXEL_VAL, PATCH_WIDTH * i + j);}
            }
            else if(NUM_PIXEL_VAL == 3){
                if(pixelGrid[y+i][x+j] == GRAY){ret += pow(NUM_PIXEL_VAL, PATCH_WIDTH * i + j);}
                else if(pixelGrid[y+i][x+j] == BLACK){ret += 2*pow(NUM_PIXEL_VAL, PATCH_WIDTH * i + j);}
            }
        }
    }
    return ret;
}

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
