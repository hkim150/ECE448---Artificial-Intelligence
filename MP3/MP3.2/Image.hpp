#ifndef Image_hpp
#define Image_hpp

#include <vector>
#include <cstring>
#include <iostream>

#define WIDTH   10
#define HEIGHT  25

using namespace std;

class Image{
private:
    char pixelGrid[HEIGHT][WIDTH];
public:
    Image(vector<string> data);
    bool setGrid(vector<string> data);
    void printImage() const;
    char getPixel(int x, int y) const;
    Image& operator=(const Image& other);
};

#endif
