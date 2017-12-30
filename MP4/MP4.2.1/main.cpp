#include "Pong.hpp"
#include "Agent.hpp"

#define NUM_TRIAL   100000

void wait(double time){
    time_t endTime = clock() + time * CLOCKS_PER_SEC;
    while(clock() < endTime){}
}

int main(){
    Pong pong;
    Agent agent;
    State currState, currDiscreteState, nextState, nextDiscreteState;
    int action, reward = 0, totalBounceCount = 0;
    
    for(int trial=0; trial<NUM_TRIAL; trial++){
        pong.initState();
        reward = 0;
        currState = pong.getState();
        currDiscreteState = currState.convertToDiscrete();
        while(reward != -1){
            action = agent.getBestAction(currDiscreteState);
            reward = pong.updateState(action);
            nextState = pong.getState();
            nextDiscreteState = nextState.convertToDiscrete();
            agent.updateQValue(currDiscreteState, action, reward, nextDiscreteState);
            currState = nextState;
            currDiscreteState = nextDiscreteState;
            if(trial == NUM_TRIAL-1){
                currState.visualizeState();
                wait(0.02);
            }
        }
        if(trial > 2000){totalBounceCount += pong.getBounceCount();}
    }
    cout << "Average Bounce Count: " << (double)totalBounceCount/(NUM_TRIAL-2000.0) << endl;
    
    return 0;
}
