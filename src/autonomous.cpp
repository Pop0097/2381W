/*
  Wheel diameter is 4" meaning eery ratation will move the robot 12.57".

  PATHS MADE FOR BLUE ZONE

  Path 1: (Another one is required if we are on the red team. In this case, instead of turning ccw, we will turn cw)
    Distance to first set of cubes: 12.65"
    Running distance (collecting cubes): 22"
    Turn 90º ccw
    Moving distance to wall: 21"
    Turn 90º ccw
    Distance to the goal zone: 28.8"
    Place cubes down :)

  Path 2:(Another one is required if we are on the red team. In this case, instead of turning cw, we will turn ccw)
    Diastance from first cube:  5.65"
    Running distance (collecting cubes): 5.5"
    Distance to second cube:  18"
    Running distance (collecting cubes): 5.5"
    Turn 90º cw
    Distance to wall: 24.4"
    Turn 90º cw
    Distance to goal zone: 23.3"
    Place cubes down :)
*/
/*
#include "main.h"
#include <math.h>

//define ports for motors
#define MOTOR1 2 //L1
#define MOTOR2 3 //L2
#define MOTOR3 11 //R1
#define MOTOR4 12 //R2

#define MOTOR5 13 //Angler
#define MOTOR6 4 //Arm  -1.243
#define MOTOR7 5 //LIntake
#define MOTOR8 14 //RIntake

Motor left_wheels_1(MOTOR1, 0); //L1
Motor right_wheels_1(MOTOR3, 1); //R1
Motor left_wheels_2(MOTOR2, 1); //L2
Motor right_wheels_2(MOTOR4, 0); //R2
Motor intake_left(MOTOR7, 0);
Motor intake_right(MOTOR8, 1);
Motor angler(MOTOR5, 1);
Motor arm(MOTOR6, 1);

void expand(void*){

}

//Will be used to call functions which will run the robot
void autonomous() {

  //PATH 1 (Blue)

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(0.55, 100);
  left_wheels_2.move_absolute(0.55, 100);
  right_wheels_1.move_absolute(0.55, 100);
  right_wheels_2.move_absolute(0.55, 100);
  while (!((left_wheels_1.get_position() < 0.6) && (left_wheels_1.get_position() > 0.5))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(0.55, -100);
  left_wheels_2.move_absolute(0.55, -100);
  right_wheels_1.move_absolute(0.55, -100);
  right_wheels_2.move_absolute(0.55, -100);
  while (!((left_wheels_1.get_position() < 0.6) && (left_wheels_1.get_position() > 0.5))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  expand();

  left_wheels_1.move_absolute(1, 100);
  left_wheels_2.move_absolute(1, 100);
  right_wheels_1.move_absolute(1, 100);
  right_wheels_2.move_absolute(1, 100);
  while (!((left_wheels_1.get_position() < 1.05) && (left_wheels_1.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  intake_left.move(100);
  intake_right.move(100);
  left_wheels_1.move_absolute(1.75, 20);
  left_wheels_2.move_absolute(1.75, 20);
  right_wheels_1.move_absolute(1.75, 20);
  right_wheels_2.move_absolute(1.75, 20);

  while (!((left_wheels_1.get_position() < 1.80) && (left_wheels_1.get_position() > 1.70))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //Code to rotate ccw 90º
  left_wheels_1.move_absolute(0.5, -100);
  left_wheels_2.move_absolute(0.5, -100);
  right_wheels_1.move_absolute(0.5, 100);
  right_wheels_2.move_absolute(0.5, 100);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(1.7, 100);
  left_wheels_2.move_absolute(1.7, 100);
  right_wheels_1.move_absolute(1.7, 100);
  right_wheels_2.move_absolute(1.7, 100);

  while (!((left_wheels_1.get_position() < 1.75) && (left_wheels_1.get_position() > 1.65))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //Code to rotate ccw 90º
  left_wheels_1.move_absolute(0.5, -100);
  left_wheels_2.move_absolute(0.5, -100);
  right_wheels_1.move_absolute(0.5, 100);
  right_wheels_2.move_absolute(0.5, 100);

  left_wheels_1.move_absolute(2.3, 100);
  left_wheels_2.move_absolute(2.3, 100);
  right_wheels_1.move_absolute(2.3, 100);
  right_wheels_2.move_absolute(2.3, 100);

  while (!((left_wheels_1.get_position() < 2.35) && (left_wheels_1.get_position() > 2.25))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //Code to place the cubes in the goal zone
  angler.tare_position();
  angler.move(1, 70);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move(1, 40);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move(0.33, 10);
  while (!((angler.get_position() < 0.35) && (angler.get_position() > 0.30))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //moves forward to make sure tht the the stack is stable
  left_wheels_1.move_absolute(0.1, 20);
  left_wheels_2.move_absolute(0.1, 20);
  right_wheels_1.move_absolute(0.1, 20);
  right_wheels_2.move_absolute(0.1, 20);
  while (!((angler.get_position() < 0.05) && (angler.get_position() > 0.15))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //backs away
  //intake_right.move(-20);
  //intake_right.move(-20);
  left_wheels_1.move_absolute(1, -20);
  left_wheels_2.move_absolute(1, -20);
  right_wheels_1.move_absolute(1, -20);
  right_wheels_2.move_absolute(1, -20);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  //intake_left.move(0);
  //intake_right.move(0);






  //PATH 2
  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(0.55, 100);
  left_wheels_2.move_absolute(0.55, 100);
  right_wheels_1.move_absolute(0.55, 100);
  right_wheels_2.move_absolute(0.55, 100);
  while (!((left_wheels_1.get_position() < 0.6) && (left_wheels_1.get_position() > 0.5))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(0.55, -100);
  left_wheels_2.move_absolute(0.55, -100);
  right_wheels_1.move_absolute(0.55, -100);
  right_wheels_2.move_absolute(0.55, -100);
  while (!((left_wheels_1.get_position() < 0.6) && (left_wheels_1.get_position() > 0.5))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  expand();

  intake_left.move(100);
  intake_right.move(100);
  left_wheels_1.move_absolute(0.45, 100);
  left_wheels_2.move_absolute(0.45, 100);
  right_wheels_1.move_absolute(0.45, 100);
  right_wheels_2.move_absolute(0.45, 100);
  while (!((left_wheels_1.get_position() < 0.50) && (left_wheels_1.get_position() > 0.40))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //sets current positions to zero
  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(0.45, 20);
  left_wheels_2.move_absolute(0.45, 20);
  right_wheels_1.move_absolute(0.45, 20);
  right_wheels_2.move_absolute(0.45, 20);
  while (!((left_wheels_1.get_position() < 0.50) && (left_wheels_1.get_position() > 0.40))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  intake_left.move(0);
  intake_right.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(1.43, 100);
  left_wheels_2.move_absolute(1.43, 100);
  right_wheels_1.move_absolute(1.43, 100);
  right_wheels_2.move_absolute(1.43, 100);
  while (!((left_wheels_1.get_position() < 1.45) && (left_wheels_1.get_position() > 1.40))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  intake_left.move(100);
  intake_right.move(100);
  left_wheels_1.move_absolute(0.45, 20);
  left_wheels_2.move_absolute(0.45, 20);
  right_wheels_1.move_absolute(0.45, 20);
  right_wheels_2.move_absolute(0.45, 20);
  while (!((left_wheels_1.get_position() < 0.50) && (left_wheels_1.get_position() > 0.40))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  intake_left.move(0);
  intake_right.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //Code to rotate cw 90º
  left_wheels_1.move_absolute(0.5, 100);
  left_wheels_2.move_absolute(0.5, 100);
  right_wheels_1.move_absolute(0.5, -100);
  right_wheels_2.move_absolute(0.5, -100);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(1.92, 100);
  left_wheels_2.move_absolute(1.92, 100);
  right_wheels_1.move_absolute(1.92, 100);
  right_wheels_2.move_absolute(1.92, 100);
  while (!((left_wheels_1.get_position() < 1.95) && (left_wheels_1.get_position() > 1.90))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //Code to rotate cw 90º
  left_wheels_1.move_absolute(0.5, 100);
  left_wheels_2.move_absolute(0.5, 100);
  right_wheels_1.move_absolute(0.5, -100);
  right_wheels_2.move_absolute(0.5, -100);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  left_wheels_1.move_absolute(0.97, 100);
  left_wheels_2.move_absolute(0.97, 100);
  right_wheels_1.move_absolute(0.97, 100);
  right_wheels_2.move_absolute(0.97, 100);
  while (!((left_wheels_1.get_position() < 1) && (left_wheels_1.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //Code to place the cubes in the goal zone
  angler.tare_position();
  angler.move(1, 100);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move(1, 90);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move(0.33, 70);
  while (!((angler.get_position() < 0.35) && (angler.get_position() > 0.30))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //moves forward to make sure tht the the stack is stable
  left_wheels_1.move_absolute(0.1, 20);
  left_wheels_2.move_absolute(0.1, 20);
  right_wheels_1.move_absolute(0.1, 20);
  right_wheels_2.move_absolute(0.1, 20);
  while (!((angler.get_position() < 0.05) && (angler.get_position() > 0.15))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  left_wheels_1.tare_position();
  left_wheels_2.tare_position();
  right_wheels_1.tare_position();
  right_wheels_2.tare_position();

  //backs away
  //intake_right.move(-20);
  //intake_right.move(-20);
  left_wheels_1.move_absolute(1, -20);
  left_wheels_2.move_absolute(1, -20);
  right_wheels_1.move_absolute(1, -20);
  right_wheels_2.move_absolute(1, -20);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  //intake_left.move(0);
  //intake_right.move(0);

}
*/
