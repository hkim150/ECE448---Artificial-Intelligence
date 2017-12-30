#ifndef Image_hpp
#define Image_hpp

#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>

#define BLACK   '#'
#define GRAY    '+'
#define WHITE   ' '
#define WIDTH   28
#define HEIGHT  28
///////////////////////////////////////////////////////////////////////
///////////////////////////// Modify Here /////////////////////////////
///////////////////////////////////////////////////////////////////////
#define LAPLACE_K       0.1
#define PATCH_WIDTH     3
#define PATCH_HEIGHT    4
                        /* DISJOINT or OVERLAP */
#define METHOD          OVERLAP

                        /* Binary(2) or Ternery(3) */
#define NUM_PIXEL_VAL   3
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define NUM_CLASS       10
#define NUM_PATCH_VAL   pow(NUM_PIXEL_VAL, PATCH_WIDTH * PATCH_HEIGHT)
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
