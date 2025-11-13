//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by tanvi, 23-09.2025

#include "Ball.h"


Ball::Ball() {//default constructor that does nothing
}
//another constructor that sets the x and y coordinates, height, width, velocity_x, velocity_y and id. height and width are 1.
Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id) {
    this->x = x;
    this->y = y;
    this->velocity_x = velocity_x;
    this->velocity_y = velocity_y;
    this->id = id;
    this->width = 1;
    this->height = 1;
}
double Ball::getX() {//getX() returns the value of the x coordinate
    return x;
}

int Ball::getID() {//getID() returns the value of the id of the ball
    return id;
}

void Ball::update() {
    //update() would first account for the change in the velocity in the y direction due to gravity
    //velocity_y = velocity_y - 0.02 * timeStep
    velocity_y = velocity_y - 0.02 * timeStep;
    
    //hen updates the x and y coordinates of the ball for one time step timeStep
    x += velocity_x * timeStep;
    y += velocity_y * timeStep;
}

int Ball::overlap(Ball& b) {
    //overlap(Ball& b) should first check if the ball of the current instance collides with ball b.
    return NO_OVERLAP;//You can have it return NO_OVERLAP
}

// Check overlap with player
int Ball::overlap(Player& p) {
    // should first check if the ball of the current instance collides with the player p
    if (x < p.getX() + p.getWidth() && x + width > p.getX() &&
        y < p.getY() + p.getHeight() && y + height > p.getY()) {
        double hoverlap = std::min(x + width, p.getX() + p.getWidth()) - std::max(x, p.getX());
        double voverlap = std::min(y + height, p.getY() + p.getHeight()) - std::max(y, p.getY());        
        if (voverlap > hoverlap) {
            return VERTICAL_OVERLAP;
        } else {
            return HORIZONTAL_OVERLAP;
        }
    }
    return NO_OVERLAP;
}


void Ball::bounce(Ball arr[], int ballCount, Player player) {
    //bounces of  wall or the paddle of the player. 
    //skipping bounce of other balls
    if (overlap(player)) {
        velocity_x = -velocity_x; 
    }
   
    //right wall
    if (x >= WIDTH - 1) {
        velocity_x = -velocity_x;
        x = WIDTH - 1;
    }
    
    //top wall
    if (y <= 0) {
        velocity_y = -velocity_y;
        y=0;
    }
    
    //bottom wall
    if (y >= HEIGHT - 1) {
        velocity_y = -velocity_y;
        y=HEIGHT-1;
    }
    
    
}

void Ball::draw(Screen& screen_to_draw_to) {
    screen_to_draw_to.addPixel(x, y, 'o');
}
//draw(Screen& screen_to_draw_to) renders the ball on the game window by calling addPixel on the screen_to_draw_to 
// object (an instance of the Screen class). The addPixel function prototype is void addPixel(double x, double y, char symbol),
//  where x and y are the coordinates, and symbol is 'o' (lower case letter O). Since the width and height of the ball is 1, 
// we only call addPixel once.