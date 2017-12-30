#ifndef Pong_hpp
#define Pong_hpp

#include "State.hpp"

class Pong{
private:
    int bouncCount;
    State state;
public:
    Pong();
    void initState();
    State getState() const;
    int getBounceCount() const;
    int updateState(int action);
    double getRandomAcceleration();
};

#endif
