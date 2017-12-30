/*
 * The Image class is for creating Image objects from the parsed data
 * It is simply a container for the feature values and its class
 * The feature values are stored in heap so it can have different width and height
 */

#ifndef Image_hpp
#define Image_hpp

#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>

#define BLACK       '#'
#define GRAY        '+'
#define WHITE       ' '
#define WIDTH       28
#define HEIGHT      28
#define NUM_FEAT    WIDTH * HEIGHT
#define NUM_CLASS   10

using namespace std;

class Image{
private:
    int classify = -1;
    int** feature = NULL;
    void makeNewFeatureSpace();
    void deleteFeature();
public:
    Image();
    Image(vector<string> data);
    ~Image();
    void printFeature() const;
    int getClass() const;
    void setClass(char num);
    int** getFeature();
    int getFeatureAt(int x, int y) const;
    Image& operator=(const Image& other);
};

#endif
