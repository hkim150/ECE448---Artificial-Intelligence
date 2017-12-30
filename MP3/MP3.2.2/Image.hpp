#ifndef Image_hpp
#define Image_hpp

#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>

#define LOW     '%'
#define HIGH    ' '
#define WIDTH   13
#define HEIGHT  30
//////////////////////////////////////////////////////////////////////
#define LAPLACE_K       0.1
#define PATCH_WIDTH     2
#define PATCH_HEIGHT    2
                        /* DISJOINT or OVERLAP */
#define METHOD          OVERLAP
//////////////////////////////////////////////////////////////////////
#define NUM_CLASS       5
#define NUM_FEAT_VAL    pow(2, PATCH_WIDTH * PATCH_HEIGHT)
#define NUM_DSJNT_PATCH (WIDTH/PATCH_WIDTH) * (HEIGHT/PATCH_HEIGHT)
#define NUM_OVRLP_PATCH (WIDTH - PATCH_WIDTH + 1) * (HEIGHT - PATCH_HEIGHT + 1)
#define DISJOINT        true
#define OVERLAP         false


using namespace std;

class Image{
private:
    int classify = -1;                      // classification of the image
    char pixelGrid[HEIGHT][WIDTH] = {};     // grid for holding pixels
public:
    Image(vector<string> data);             // copy constructor
    bool setGrid(vector<string> data);      // overwrite the copied image
    void printImage() const;                // prints the charactors in pixel grid
    int getClass() const;                   // classification getter
    void setClass(int num);                 // classification setter
    char getPixel(int x, int y) const;      // pixel charactor getter
    vector<int> getDisjointPatchValue();    // returns vector of disjoint feature values
    vector<int> getOverlapPatchValue();     // returns vector of overlapping feature values
    int getPatchValue(int x, int y) const;  // returns location's feature value
    Image& operator=(const Image& other);   // copy assignment operator
};

#endif
