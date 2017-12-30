#include "Pong.hpp"

Pong::Pong(){
    srand((unsigned int)time(NULL));
    initState();
}

void Pong::initState(){
    bouncCount = 0;
    state.ball_x = WIDTH/2.0;
    state.ball_y = HEIGHT/2.0;
    state.velocity_x = 0.03;
    state.velocity_y = 0.01;
    state.paddle_y = (HEIGHT - PADDLE_HEIGHT)/2.0;
}

int Pong::updateState(int action){
    int reward = 0;
    if(action == UP){
        if(state.paddle_y - PADDLE_DISPLACEMENT < 0){state.paddle_y = 0.0;}
        else{state.paddle_y -= PADDLE_DISPLACEMENT;}
    }
    else if(action == DOWN){
        if(state.paddle_y + PADDLE_DISPLACEMENT > HEIGHT - PADDLE_HEIGHT){state.paddle_y = HEIGHT - PADDLE_HEIGHT;}
        else{state.paddle_y += PADDLE_DISPLACEMENT;}
    }
    state.ball_y += state.velocity_y;
    if(state.ball_y < 0){
        state.ball_y *= -1.0;
        state.velocity_y *= -1.0;
    }
    else if(state.ball_y > HEIGHT){
        state.ball_y = 2.0 * HEIGHT - state.ball_y;
        state.velocity_y *= -1.0;
    }
    state.ball_x += state.velocity_x;
    if(state.ball_x < 0){
        state.ball_x *= -1.0;
        state.velocity_x *= -1.0;
    }
    else if(state.ball_x >= WIDTH){
        if(state.ball_y >= state.paddle_y && state.ball_y <= state.paddle_y + PADDLE_HEIGHT){
            state.ball_x = 2.0 * WIDTH - state.ball_x;
            state.velocity_x *= -1.0;
            double a;
            do{a = getRandomAcceleration();}
            while(state.velocity_y + 2.0 * a <= -1.0 * MAX_VELOCITY);
            state.velocity_y += 2.0 * a;
            do{a = getRandomAcceleration();}
            while(state.velocity_x + a >= -1.0 * MIN_VELOCITY_X || state.velocity_x + a <= -1.0 * MAX_VELOCITY);
            state.velocity_x += a;
            reward = 1;
            bouncCount++;
        }
        else{reward = -1;}
    }
    return reward;
}

State Pong::getState() const{return state;}

int Pong::getBounceCount() const{return bouncCount;}

double Pong::getRandomAcceleration(){return (((double)(rand()%31)-15.0))/1000.0;}
