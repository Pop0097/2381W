#include "main.h"
#include "pid.h"

//defines the ports for each motor
#define MOTOR1 2 //L1
#define MOTOR2 3 //L2
#define MOTOR3 11 //R1
#define MOTOR4 12 //R2

#define MOTOR5 13 //Angler
#define MOTOR6 4 //Arm
#define MOTOR7 5 //LIntake9
#define MOTOR8 14 //RIntake

PID pid = PID(0.1, 75, -75, 10, 1, 0.5);//constructs PID object
//PID pid_auton = PID(0.1, 75, -75, 10, 1, 0.5);
//defines controller
pros::Controller master (CONTROLLER_MASTER);
pros::Mutex mutex;

//defines the ports that are associated with each wheel
pros::Motor left_wheels_1 (MOTOR1, 1); //L1
pros::Motor right_wheels_1 (MOTOR3, 0); //R1
pros::Motor left_wheels_2 (MOTOR2, 1); //L2
pros::Motor right_wheels_2 (MOTOR4, 0); //R2

pros::Motor intake_left (MOTOR7, 1);
pros::Motor intake_right (MOTOR8, 0);
pros::Motor arm (MOTOR6, 1);
pros::Motor angler (MOTOR5, 0);

void autonomousOne();
void autonomousTwo();
void autonomousThree();
void autonomousFour();
void expand();

void drive(void*) {

//loop reads the joystick controlls and powers the motors accordingly
	while (true) {
		int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = power + turn;
		int right = power - turn;
		left_wheels_1.move(left);
		left_wheels_2.move(left);
		right_wheels_1.move(right);
		right_wheels_2.move(right);
		pros::delay(20);
	}
}

void intake(void*) {

	int intake_power = 100;
	//moves intakes
	while(true) {
		if(master.get_digital(DIGITAL_R2)) {
			intake_left.move(intake_power);
			intake_right.move(intake_power);
		}
		else if(master.get_digital(DIGITAL_L2)) {
			intake_left.move(-intake_power);
			intake_right.move(-intake_power);
		}
		else if(master.get_digital(DIGITAL_B)) {
			intake_left.move(intake_power/3);
			intake_right.move(intake_power/3);
				while (!master.get_digital(DIGITAL_B)) {
				   pros::delay(20);
				}
		}
		else {
			intake_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			intake_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		pros::delay(20);
	}
}

void arms(void*) {

	int arm_power = 100;

	while(true) {
		//moves arm
		if(master.get_digital(DIGITAL_UP)) {
			arm.move(arm_power);
		}
		else if(master.get_digital(DIGITAL_DOWN)) {
			arm.move(-arm_power);
		}
		else {
			arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		pros::delay(20);
	}
}

void anglerMove(void*) {

	while(true) {
			int angler_power = pid.calculate(3, angler.get_position());
				//moves angler
			if(master.get_digital(DIGITAL_R1)) {
				angler.move(angler_power);
			}
			else if(master.get_digital(DIGITAL_L1)) {
				angler.move(-angler_power);
			}
			else {
				angler.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			}
			pros::delay(20);
		}
}

void towerScore(void*) {

	while(true) {

		if(master.get_digital(DIGITAL_A)) {

			mutex.take(TIMEOUT_MAX);

			arm.set_zero_position(0);
			arm.move_absolute(100, 100); //change values later to not damage robot!
			while (!((arm.get_position() < 105) && (arm.get_position() > 95))) {
		    pros::delay(20);
		  }
			intake_left.move_relative(360, -100); //change values later to not damage robot!
			intake_right.move_relative(360, -100); //change values later to not damage robot!
			while (!((intake_left.get_position() < 365) && (intake_left.get_position() > 355))) {
		    	pros::delay(20);
		  }
			arm.move_absolute(0, -100); //change values later to not damage robot!
			while (!((arm.get_position() < 5) && (arm.get_position() > -5))) {
		    	pros::delay(20);
		  }

			mutex.give();
		}
	}
}

void stacker(void*) {

	while(true) {

		if(master.get_digital(DIGITAL_X)) {

			mutex.take(TIMEOUT_MAX);

			angler.set_zero_position(0);
			angler.move_absolute(100, 100); //change values later to not damage robot!
			while (!((angler.get_position() < 105) && (angler.get_position() > 95))) {
				pros::delay(20);
			}

			left_wheels_1.move_relative(45, 50); //change values later to not damage robot!
			left_wheels_2.move_relative(45, 50); //change values later to not damage robot!
			right_wheels_1.move_relative(45, 50); //change values later to not damage robot!
			right_wheels_2.move_relative(45, 50); //change values later to not damage robot!
			while (!((left_wheels_1.get_position() < 50) && (left_wheels_1.get_position() > 40))) {
				pros::delay(20);
			}

			mutex.give();
		}
	}
}

void auton(void*) {
	while(true){
		if(master.get_digital(DIGITAL_LEFT)){
			autonomousOne();
		}
		if(master.get_digital(DIGITAL_X)){
			autonomousTwo();
		}
		if(master.get_digital(DIGITAL_A)){
			autonomousThree();
		}
		if(master.get_digital(DIGITAL_Y)){
			autonomousFour();
		}
	}
}

void opcontrol() {
	pros::Task task1 (drive, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Driving");
	pros::Task task2 (intake, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake");
	pros::Task task3 (anglerMove, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Angler");
	pros::Task task4 (arms, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arms");
	pros::Task task5 (towerScore, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Tower scoring");
	pros::Task task6 (stacker, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Cube stacking");
	pros::Task task7 (auton, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Autonomous");
}

void expand(){
	arm.tare_position();
	arm.move_absolute(2, 100);
	while (!((arm.get_position() < 2.05) && (arm.get_position() > 1.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }
	angler.tare_position();
	angler.move_absolute(0.5, 100);
	while (!((angler.get_position() < 0.55) && (angler.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }
	arm.move_absolute(2, -70);
	while (!((arm.get_position() < 2.05) && (arm.get_position() > 1.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }
	angler.move_absolute(0.5, -70);
	while (!((angler.get_position() < 0.55) && (angler.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }
}

void autonomousOne(){//Path 1 Blue

	pros::lcd::set_text(1, "Auton1");

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
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

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
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

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
  angler.move_absolute(1, 100);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(1, 90);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(0.33, 70);
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
  while (!((left_wheels_1.get_position() < 0.05) && (left_wheels_1.get_position() > 0.15))) {
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

void autonomousTwo(){

	pros::lcd::set_text(1, "Auton2");

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

	//Code to rotate cw 90º
  left_wheels_1.move_absolute(0.5, 100);
  left_wheels_2.move_absolute(0.5, 100);
  right_wheels_1.move_absolute(0.5, -100);
  right_wheels_2.move_absolute(0.5, -100);
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

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

  //Code to rotate cw 90º
  left_wheels_1.move_absolute(0.5, 100);
  left_wheels_2.move_absolute(0.5, 100);
  right_wheels_1.move_absolute(0.5, -100);
  right_wheels_2.move_absolute(0.5, -100);
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

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
  angler.move_absolute(1, 100);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(1, 90);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(0.33, 70);
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
  while (!((left_wheels_1.get_position() < 0.05) && (left_wheels_1.get_position() > 0.15))) {
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
} //Path 1 Red

void autonomousThree(){ //Path 2 Blue

	pros::lcd::set_text(1, "Auton3");
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
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

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
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

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
  angler.move_absolute(1, 100);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(1, 90);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(0.33, 70);
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
  while (!((left_wheels_1.get_position() < 0.05) && (left_wheels_1.get_position() > 0.15))) {
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

void autonomousFour(){

	pros::lcd::set_text(1, "Auton4");
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

	//Code to rotate ccw 90º
	left_wheels_1.move_absolute(0.5, -100);
	left_wheels_2.move_absolute(0.5, -100);
	right_wheels_1.move_absolute(0.5, 100);
	right_wheels_2.move_absolute(0.5, 100);
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
	 // Continue running this loop as long as the motor is not within +-5 units of its goal
	 pros::delay(2);
	}

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

	//Code to rotate ccw 90º
	left_wheels_1.move_absolute(0.5, -100);
	left_wheels_2.move_absolute(0.5, -100);
	right_wheels_1.move_absolute(0.5, 100);
	right_wheels_2.move_absolute(0.5, 100);
	while (!((left_wheels_1.get_position() < 0.55) && (left_wheels_1.get_position() > 0.45))) {
	 // Continue running this loop as long as the motor is not within +-5 units of its goal
	 pros::delay(2);
	}

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
  angler.move_absolute(1, 100);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(1, 90);
  while (!((angler.get_position() < 1.05) && (angler.get_position() > 0.95))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

  angler.tare_position();
  angler.move_absolute(0.33, 70);
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
  while (!((left_wheels_1.get_position() < 0.05) && (left_wheels_1.get_position() > 0.15))) {
   // Continue running this loop as long as the motor is not within +-5 units of its goal
   pros::delay(2);
  }

	left_wheels_1.move(0);
	left_wheels_2.move(0);
	right_wheels_1.move(0);
	right_wheels_2.move(0);
	//intake_left.move(0);
	//intake_right.move(0);
} //Path 2 Red
