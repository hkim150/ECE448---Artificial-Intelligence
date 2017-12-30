#include "State.hpp"

State State::convertToDiscrete() const{
    State ret;
    if(ball_x > WIDTH){ret.ball_x = DISCRETE_WIDTH;}
    else{
        ret.ball_x = floor(ball_x*DISCRETE_WIDTH);
        if(ret.ball_x == DISCRETE_WIDTH){ret.ball_x = DISCRETE_WIDTH - 1;}
    }
    ret.ball_y = floor(ball_y*DISCRETE_HEIGHT);
    if(ret.ball_y == DISCRETE_HEIGHT){ret.ball_y = DISCRETE_HEIGHT - 1;}
    if(velocity_x >= 0){ret.velocity_x = 1;}
    else{ret.velocity_x = 0;}
    if(velocity_y >= 0.015){ret.velocity_y = 2;}
    else if(velocity_y <= -0.015){ret.velocity_y = 0;}
    else{ret.velocity_y = 1;}
    ret.paddle_y = floor(DISCRETE_HEIGHT * paddle_y/(HEIGHT - PADDLE_HEIGHT));
    if(ret.paddle_y == DISCRETE_HEIGHT){ret.paddle_y = DISCRETE_HEIGHT - 1;}
    return ret;
}

void State::printState() const{
    cout << "ball_x: " << ball_x;
    cout << ", ball_y: " << ball_y;
    cout << ", vel_x: " << velocity_x;
    cout << ", vel_y: " << velocity_y;
    cout << ", paddle_y: " << paddle_y;
    cout << endl;
}

void State::visualizeState() const{
    for(double i=0; i<=HEIGHT+0.04; i+=0.04){
        for(double j=0; j<=WIDTH+0.02; j+=0.02){
            if(i==0 || (i<=HEIGHT+0.015 && i>=HEIGHT-0.015) || j==0){cout << '#';}
            else if((j<=WIDTH+0.01 && j>=WIDTH-0.01) && i>=paddle_y && i<=paddle_y+PADDLE_HEIGHT*HEIGHT){cout << '|';}
            else if(j<=ball_x+0.009 && j>=ball_x-0.009 && i<=ball_y+0.02 && i>=ball_y-0.02){cout << 'o';}
            else{cout << ' ';}
        }
        cout << endl;
    }
}

State& State::operator=(const State& other){
    if(this != &other){
        ball_x = other.ball_x;
        ball_y = other.ball_y;
        velocity_x = other.velocity_x;
        velocity_y = other.velocity_y;
        paddle_y = other.paddle_y;
    }
    return *this;
}
