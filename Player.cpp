//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Tanvi, 23-09-2025

#include "Player.h"

Player::Player (){//default constructor does nothing

}
Player::Player (double x, double y, int height){//another constructor sets the x and y coordinates, height and width
    this->x=x; //sets playe's x coordinatr to x
    this->y=y; //sets y coordinate to y
    this->height=height;//height to height 
    this->width=1; //its default
}

double Player::getX(){//getX() returns the value of the x coordinate
    return x;
}

double Player::getY(){//getY() returns the value of the y coordinate
    return y;
}

int Player::getHeight(){//getHeight() returns the height of the paddle
    return height;
}
int Player::getWidth(){//getWidth() returns the width of the paddle
    return width;
}

void Player::decreaseHeight(int delta_to_decrease_by){//decreaseHeight(int delta_to_decrease_by) decreases the height by delta_to_decrease_by amount. The minimum height is 3.
    height-= delta_to_decrease_by;
    if(height<3){
        height=3;//minimum height is 3
    }
}

void Player::update(char c){
    //update(char c) updates the y coordinates of the paddle according to the value of c. 
    // If the user presses the up arrow key (represented by c == 'A'), the y coordinate should increase by the value of 2. 
   
    if (c=='A'){
        y+=2;

     // Conversely, if the down arrow key is pressed (c == 'B'), 
    // the y coordinate should decrease by the value of 2. 
    }else if(c=='B'){
        y-=2;

    }
 // The paddle should not fall below the floor or above the ceiling.
 //  Hence, you should limit the y-coordinate to the minimum y or the maximum y, 
 // respectively, if needed. In Fig. 2, we show the paddle x and y coordinates with respect to the game window to help you figure out the allowed range of the y coordinate.
    
    if(y<0){
        y=0;
    }
    if (y + height > HEIGHT) {
        y = HEIGHT - height;
    }
}

//paddle with '#' for paddle pixel
void Player::draw(Screen& screen_to_draw_to) {//draw(Screen& screen_to_draw_to) renders the paddle on the game window by invoking addPixel on the screen_to_draw_to object (an instance of the Screen class). 
// The addPixel function prototype is void addPixel(double x, double y, char symbol), where x and y are the coordinates of the pixel/point we want to draw, and symbol is #. 
// To draw the paddle, call addPixel repeatedly on each pixel/point of the paddle. 
// In Fig. 3, we show the game printed on the terminal. The paddle is shown with #.
    for (int i = 0; i < height; i++) {
        screen_to_draw_to.addPixel(x, y + i, '#');
    }

}