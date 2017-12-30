#ifndef Image_hpp
#define Image_hpp

#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>

#define BLACK   '#'
#define WHITE   ' '
#define WIDTH   60
#define HEIGHT  70
/////////////////////////////////////////////////////////////////////////
#define LAPLACE_K       0.1
#define PATCH_WIDTH     4
#define PATCH_HEIGHT    2
                        /* DISJOINT or OVERLAP */
#define METHOD          OVERLAP
/////////////////////////////////////////////////////////////////////////
#define NUM_CLASS       2
#define NUM_FEAT_VAL    pow(2, PATCH_WIDTH * PATCH_HEIGHT)
#define NUM_DSJNT_PATCH (WIDTH/PATCH_WIDTH) * (HEIGHT/PATCH_HEIGHT)
#define NUM_OVRLP_PATCH (WIDTH - PATCH_WIDTH + 1) * (HEIGHT - PATCH_HEIGHT + 1)
#define DISJOINT        true
#define OVERLAP         false


using namespace std;

class Image{
private:
    int classify = -1;
    char pixelGrid[HEIGHT][WIDTH] = {};
public:
    Image(vector<string> data);
    bool setGrid(vector<string> data);
    void printImage() const;
    int getClass() const;
    void setClass(char num);
    char getPixel(int x, int y) const;
    vector<int> getDisjointPatchValue();
    vector<int> getOverlapPatchValue();
    int getPatchValue(int x, int y) const;
    Image& operator=(const Image& other);
};

#endif
