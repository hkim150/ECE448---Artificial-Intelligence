#ifndef Image_hpp
#define Image_hpp

#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>

#define BLACK           '#'
#define GRAY            '+'
#define WHITE           ' '
#define WIDTH           28
#define HEIGHT          28
#define NUM_FEAT        WIDTH * HEIGHT
#define NUM_CLASS       10
#define NUM_PIXEL_VAL   3

using namespace std;

class Image{
private:
    int classify = -1;
    double** feature = NULL;
    void makeNewFeatureSpace();
    void deleteFeature();
public:
    Image();
    Image(vector<string> data);
    ~Image();
    void printFeature() const;
    int getClass() const;
    void setClass(char num);
    double** getFeature();
    double getFeatureAt(int x, int y) const;
    Image& operator=(const Image& other);
};

#endif

