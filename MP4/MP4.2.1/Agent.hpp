#ifndef Agent_hpp
#define Agent_hpp

#include <cmath>
#include "State.hpp"

#define GAMMA   0.7
#define C       50.0

class Agent{
private:
    double****** QTable;
    int****** NTable;
public:
    Agent();
    ~Agent();
    double getQValue(State discreteState, int action) const;
    void setQValue(State discreteState, int action, double newValue);
    int getNValue(State discreteState, int action) const;
    void incrementNValue(State discreteState, int action);
    void updateQValue(State discreteState, int action, int reward, State nextDiscreteState);
    int getBestAction(State discreteState) const;
    void printNoneZeroQValCount() const;
};

#endif
