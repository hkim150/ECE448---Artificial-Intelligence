#include "Agent.hpp"

Agent::Agent(){
    //QTable = new double [DISCRETE_WIDTH*DISCRETE_HEIGHT*NUM_DISCRETE_X_VELOCITY*NUM_DISCRETE_Y_VELOCITY*NUM_DISCRETE_PADDLE_LOC*NUM_ACTION + 1];
    QTable = new double***** [DISCRETE_WIDTH+1];
    for(int i=0; i<DISCRETE_WIDTH+1; i++){
        QTable[i] = new double**** [DISCRETE_HEIGHT];
        for(int j=0; j<DISCRETE_HEIGHT; j++){
            QTable[i][j] = new double*** [NUM_DISCRETE_X_VELOCITY];
            for(int k=0; k<NUM_DISCRETE_X_VELOCITY; k++){
                QTable[i][j][k] = new double** [NUM_DISCRETE_Y_VELOCITY];
                for(int l=0; l<NUM_DISCRETE_Y_VELOCITY; l++){
                    QTable[i][j][k][l] = new double* [NUM_DISCRETE_PADDLE_LOC];
                    for(int m=0; m<NUM_DISCRETE_PADDLE_LOC; m++){
                        QTable[i][j][k][l][m] = new double [NUM_ACTION];
                        for(int n=0; n<NUM_ACTION; n++){
                            QTable[i][j][k][l][m][n] = 0.0;
                        }
                    }
                }
            }
        }
    }
    //NTable = new int [DISCRETE_WIDTH*DISCRETE_HEIGHT*NUM_DISCRETE_X_VELOCITY*NUM_DISCRETE_Y_VELOCITY*NUM_DISCRETE_PADDLE_LOC*NUM_ACTION + 1];
    NTable = new int***** [DISCRETE_WIDTH+1];
    for(int i=0; i<DISCRETE_WIDTH+1; i++){
        NTable[i] = new int**** [DISCRETE_HEIGHT];
        for(int j=0; j<DISCRETE_HEIGHT; j++){
            NTable[i][j] = new int*** [NUM_DISCRETE_X_VELOCITY];
            for(int k=0; k<NUM_DISCRETE_X_VELOCITY; k++){
                NTable[i][j][k] = new int** [NUM_DISCRETE_Y_VELOCITY];
                for(int l=0; l<NUM_DISCRETE_Y_VELOCITY; l++){
                    NTable[i][j][k][l] = new int* [NUM_DISCRETE_PADDLE_LOC];
                    for(int m=0; m<NUM_DISCRETE_PADDLE_LOC; m++){
                        NTable[i][j][k][l][m] = new int [NUM_ACTION];
                        for(int n=0; n<NUM_ACTION; n++){
                            NTable[i][j][k][l][m][n] = 0;
                        }
                    }
                }
            }
        }
    }
}

Agent::~Agent(){
    if(QTable != NULL){
        for(int i=0; i<DISCRETE_WIDTH+1; i++){
            for(int j=0; j<DISCRETE_HEIGHT; j++){
                for(int k=0; k<NUM_DISCRETE_X_VELOCITY; k++){
                    for(int l=0; l<NUM_DISCRETE_Y_VELOCITY; l++){
                        for(int m=0; m<NUM_DISCRETE_PADDLE_LOC; m++){
                            delete[] QTable[i][j][k][l][m];
                        }
                        delete[] QTable[i][j][k][l];
                    }
                    delete[] QTable[i][j][k];
                }
                delete[] QTable[i][j];
            }
            delete[] QTable[i];
        }
        delete[] QTable;
        QTable = NULL;
    }
    if(NTable != NULL){
        for(int i=0; i<DISCRETE_WIDTH+1; i++){
            for(int j=0; j<DISCRETE_HEIGHT; j++){
                for(int k=0; k<NUM_DISCRETE_X_VELOCITY; k++){
                    for(int l=0; l<NUM_DISCRETE_Y_VELOCITY; l++){
                        for(int m=0; m<NUM_DISCRETE_PADDLE_LOC; m++){
                            delete[] NTable[i][j][k][l][m];
                        }
                        delete[] NTable[i][j][k][l];
                    }
                    delete[] NTable[i][j][k];
                }
                delete[] NTable[i][j];
            }
            delete[] NTable[i];
        }
        delete[] NTable;
        NTable = NULL;
    }
}

double Agent::getQValue(State discreteState, int action) const{return QTable[(int)discreteState.ball_x][(int)discreteState.ball_y][(int)discreteState.velocity_x][(int)discreteState.velocity_y][(int)discreteState.paddle_y][action];}

void Agent::setQValue(State discreteState, int action, double newValue){QTable[(int)discreteState.ball_x][(int)discreteState.ball_y][(int)discreteState.velocity_x][(int)discreteState.velocity_y][(int)discreteState.paddle_y][action] = newValue;}

int Agent::getNValue(State discreteState, int action) const{return NTable[(int)discreteState.ball_x][(int)discreteState.ball_y][(int)discreteState.velocity_x][(int)discreteState.velocity_y][(int)discreteState.paddle_y][action];}

void Agent::incrementNValue(State discreteState, int action){NTable[(int)discreteState.ball_x][(int)discreteState.ball_y][(int)discreteState.velocity_x][(int)discreteState.velocity_y][(int)discreteState.paddle_y][action]++;}

void Agent::updateQValue(State discreteState, int action, int reward, State nextDiscreteState){
    double alpha = C/(C + sqrt(getNValue(discreteState, action)));
    double oldQValue = getQValue(discreteState, action);
    double maxNextQValue = getQValue(nextDiscreteState, getBestAction(nextDiscreteState));
    double newQValue = oldQValue + alpha * ((double)reward + GAMMA * maxNextQValue - oldQValue);
    setQValue(discreteState, action, newQValue);
    incrementNValue(discreteState, action);
}

int Agent::getBestAction(State discreteState) const{
    double maxQValue = 0.0;
    int bestAction = 0;
    for(int i=0; i<NUM_ACTION; i++){
        if(getNValue(discreteState, i) < 5){return i;}
        double currQValue = getQValue(discreteState, i);
        if(i == 0){maxQValue = currQValue;}
        else{
            if(currQValue > maxQValue){
                maxQValue = currQValue;
                bestAction = i;
            }
        }
    }
    return bestAction;
}

void Agent::printNoneZeroQValCount() const{
    int count = 0;
    for(int i=0; i<DISCRETE_WIDTH+1; i++){
        for(int j=0; j<DISCRETE_HEIGHT; j++){
            for(int k=0; k<NUM_DISCRETE_X_VELOCITY; k++){
                for(int l=0; l<NUM_DISCRETE_Y_VELOCITY; l++){
                    for(int m=0; m<NUM_DISCRETE_PADDLE_LOC; m++){
                        for(int n=0; n<NUM_ACTION; n++){
                            if(QTable[i][j][k][l][m][n] == 0.0){count++;}
                        }
                    }
                }
            }
        }
    }
    cout << "0 count: " << count << endl;
}
