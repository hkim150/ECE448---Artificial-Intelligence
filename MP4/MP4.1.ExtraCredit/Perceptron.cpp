#include "Perceptron.hpp"

Perceptron::Perceptron(bool rand_weight){
    weight = new double[NUM_FEAT];
    if(rand_weight){
        for(int i=0; i<NUM_FEAT; i++){
            weight[i] = (double)(rand()%1000 - 500)/1000.0;
        }
    }
    else{
        for(int i=0; i<NUM_FEAT; i++){
            weight[i] = 0.0;
        }
    }
}

Perceptron::~Perceptron(){
    delete[] weight;
    weight = NULL;
}

int Perceptron::signFunc(double input) const{
    if(input >= 0){return 1;}
    else{return -1;}
}

double Perceptron::sigmoidFunc(double input) const{
    return 1/(1 + pow(M_E, input));
}

double Perceptron::getOutput(double** feature, double bias) const{
    double ret = 0;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            ret += feature[i][j] * weight[i*WIDTH + j];
        }
    }
    ret += bias;
    return ret;
}

void Perceptron::updateWeight(double** feature, double alpha){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            weight[i*WIDTH + j] += alpha * (double)feature[i][j];
        }
    }
    updateCount++;
}

void Perceptron::printWeight() const{
    cout << endl;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(weight[i*WIDTH + j] > 2){cout << (int)weight[i*WIDTH + j];}
            else{cout << ' ';}
        }
        cout << endl;
    }
}

int Perceptron::getUpdateCount() const{return updateCount;}

