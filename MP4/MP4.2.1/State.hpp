#ifndef State_hpp
#define State_hpp

#include <cmath>
#include <iostream>

#define WIDTH                   1.0
#define HEIGHT                  1.0
#define PADDLE_HEIGHT           0.2
#define MIN_VELOCITY_X          0.03
#define MAX_VELOCITY            1.0
#define PADDLE_DISPLACEMENT     0.04

#define NUM_ACTION              3
#define DISCRETE_WIDTH          12
#define DISCRETE_HEIGHT         12
#define NUM_DISCRETE_X_VELOCITY 2
#define NUM_DISCRETE_Y_VELOCITY 3
#define NUM_DISCRETE_PADDLE_LOC 12

using namespace std;

enum Action{NOTHING = 0, UP, DOWN};

class State{
public:
    double ball_x, ball_y;
    double velocity_x, velocity_y;
    double paddle_y;
public:
    State convertToDiscrete() const;
    void printState() const;
    void visualizeState() const;
    State& operator=(const State& other);
};

#endif

