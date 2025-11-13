//
//  main.cpp
//  Lab 2 Pong Game
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-11
//  Copyright © 2024 Nathan Hung. No rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <string>
#include "Ball.h"
#include "Globals.h"
#include "Player.h"

#include "Screen.h"
#include "io.h"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int max_ballCount = 5;

  Ball balls_array[max_ballCount];

  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;

  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    // TODO: ECE 244 Student: Complete the game loop here only!
    // ECE 244 Student: DO NOT edit any other segments of this file!


    //using get_input() from io.cpp.
    char input = get_input();
    if (input == 'q') {//If the player types 'q', the game ends.
      gameEnded = true;
      break;
    }
    //If the user input is not '\0', the paddle moves up or down using Player methods.
    if (input != '\0') {
      player.update(input);//call player function which will either move it up or down using the player methods
    }
    //f no input is given, get_input() returns '\0', and the paddle stays in place.- defaukt behaviour 
    //Each ball moves according to its velocity.
    for(int i=0; i<simulation_fps; i++){//he game runs simulation_fps iterations of the loop before drawing to the screen. 
      for(int j=0; j<ballCount; j++){
        balls_array[j].update();//Update balls: Each ball moves according to its velocity.
      }
      //Check if balls are to bounce from the paddle/walls/ceiling.
      for (int j = 0; j < ballCount; j++) {
        if (balls_array[j].overlap(player)) {//If a ball collides with the paddle, the score increases by 1.
          score++;
          if (score % 2 == 0) {//Every 2 hits, the paddle size decreases by 1 using a method in Player class.
            player.decreaseHeight(1);
          }
          //Every 5 hits, we increase the number of balls by 1 till we have a maximum of 5 balls.
          if (score % 5 == 0 && ballCount < max_ballCount) {
            balls_array[ballCount] = Ball(30.0, 30.0, 0.9, 0, ballCount);//New balls created should have (x, y) = (30.0, 30.0), velocity_x = 0.9 and velocity_y = 0.
            ballCount++;
          }
        }
        //If a ball bounces off the left ball, the game ends.
        if (balls_array[j].getX() <= 0) {
          gameEnded = true;
          break;
        }
        //Check if balls are to bounce from the paddle/walls/ceiling.
        balls_array[j].bounce(balls_array, ballCount, player);



      }
      if(gameEnded){
        break;
      }

    }
    //When the simulation_fps time steps are complete:
    // The game renders the frame by calling the draw() methods of Ball and Player.
    // The main loop waits for the correct frame duration so that the game runs smoothly at screen_fps.
    player.draw(screen);
    for (int i = 0; i < ballCount; i++) {
      balls_array[i].draw(screen);
    }
    




    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }
  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}