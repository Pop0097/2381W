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

using namespace pros;

Motor left_wheels_1(MOTOR1, 0); //L1
Motor right_wheels_1(MOTOR3, 1); //R1
Motor left_wheels_2(MOTOR2, 1); //L2
Motor right_wheels_2(MOTOR4, 0); //R2
Motor intake_left(MOTOR7, 0);
Motor intake_right(MOTOR8, 1);
Motor angler(MOTOR5, 1);
Motor arm(MOTOR6, 1);

void expand() {
	arm.set_zero_position(0);

	arm.move(50);
	while(!(arm.get_position() > -10 && arm.get_position() < -8)){

	}
	//Moves motors to let robot expand. I DON'T WANT TO BREAK THE MOTORS SO WE HAVE TO CHANGE THE VALUES LATER


	//Moves motors to original position


	delay(20);
}

//Will be used to call functions which will run the robot
void autonomous() {

  expand();

  //basically, robot moves to cubes, picks up, stops to let cube go up, moves towards next cube, picks up and stops, and it repeats that. We can change #of repeats or if the robot has to stop at all
  left_wheels_1.move(70);
  left_wheels_2.move(70);
  right_wheels_1.move(70);
  right_wheels_2.move(70);
  intake_left.move(100);
  intake_right.move(100);
  delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  delay(1000); //idk change this value later
  left_wheels_1.move(20);
  left_wheels_2.move(20);
  right_wheels_1.move(20);
  right_wheels_2.move(20);
  delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  delay(1000); //idk change this value later
  left_wheels_1.move(20);
  left_wheels_2.move(20);
  right_wheels_1.move(20);
  right_wheels_2.move(20);
  delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  delay(1000);
  intake_left.move(0);
  intake_right.move(0);

  //Robot turns around CCW
  left_wheels_1.move(-70);
  left_wheels_2.move(-70);
  right_wheels_1.move(70);
  right_wheels_2.move(70);
  delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //Robot moves to the goal zone
  left_wheels_1.move(70);
  left_wheels_2.move(70);
  right_wheels_1.move(70);
  right_wheels_2.move(70);
  delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //THERE IS A CHANCE WE NEED TO DO THe last part DIFFERENTLY SO THAT THE ROBOT IS ALIGNED MORE PROPERLY. LET'S JUST PRAY THAT THIS WORKS

  //Robot places cubes in the goal zone
  arm.move(30); //arm moves out to protect the blocks from falling
  angler.move(30);
  delay(1000); //idk change this value later
  arm.move(0);
  delay(1000); //idl change this value later
  angler.move(0);
  delay(100);
  arm.move(100); //moves arms all the way up so that they go over the blocks (hopefully)... if they don't, we will have a very tricky situation on our hands...
  delay(1000); //idk change this value later
  arm.move(0);

  //Robot moves away from the stack :)
  left_wheels_1.move(-20);
  left_wheels_2.move(-20);
  right_wheels_1.move(-20);
  right_wheels_2.move(-20);

}
*/
