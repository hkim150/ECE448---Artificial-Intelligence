#ifndef image_hpp
#define image_hpp

#include <iostream>

#include "pixel.hpp"

using namespace std;

#define WIDTH 28
#define HEIGHT 28

class Image{
public:
    Pixel* pxl[HEIGHT][WIDTH];              // pixel grid holder
    void printImage() const;                // printing image utility function
    Image& operator=(const Image& other);   // copy assignment operator
    ~Image();                               // destructor for freeing heap
};

#endif
