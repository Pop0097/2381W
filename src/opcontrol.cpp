#include "main.h"
#include "pid.h"

//defines the ports for each motor
#define MOTOR1 14 //L1
#define MOTOR2 17 //L2
#define MOTOR3 11 //R1
#define MOTOR4 2 //R2

#define MOTOR5 13 //Angler
#define MOTOR6 4 //Arm
#define MOTOR7 5 //LIntake9
#define MOTOR8 18 //RIntake

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

void drive(void*) {

//loop reads the joystick controlls and powers the motors accordingly
	while (true) {
		int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_LEFT_X);
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
		else if(master.get_digital(DIGITAL_DOWN)) {
			intake_left.move(intake_power/3);
			intake_right.move(intake_power/3);
			while (!master.get_digital(DIGITAL_DOWN)) {
			   pros::delay(20);
			}
		}
		else {
			//ensures the intakes do not move
			intake_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			intake_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		pros::delay(20);
	}
}

void anglerMove(void*) {

	while(true){
		int power = master.get_analog(ANALOG_RIGHT_Y);
		if(power!= 0){
			angler.move(power);
		}
		else{
			angler.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		pros::delay(20);
	}

	/*
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
*/
}

void arms(void*) {

	int arm_power = 100;

	while(true) {
		//moves arm
		if(master.get_digital(DIGITAL_R1)) {
			arm.move(arm_power);
		}
		else if(master.get_digital(DIGITAL_L1)) {
			arm.move(-arm_power);
		}
		else {
			arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		pros::delay(20);
	}
}

void towerScore(void*){ //macros for the towers. Hit R1 or L1 to override
	while(true){
		if(master.get_digital(DIGITAL_RIGHT)){ //medium tower
			pros::lcd::set_text(1, "Medium tower");
			int encoderValue2 = 70;//TEMPORARY VALUE
			mutex.take(TIMEOUT_MAX);
			while(!((master.get_digital(DIGITAL_R1)) || (master.get_digital(DIGITAL_R2)))){
				if(arm.get_position() > encoderValue2){
					arm.move(-50);
				}
				else{
					arm.move(50);
				}
				if(!((arm.get_position() < 65) && (arm.get_position() > 75))){ //TEMPORARY VALUES
					pros::delay(20);
				}
				else{
					arm.move(0);
				}
			}
			mutex.give();
		}
		else if(master.get_digital(DIGITAL_LEFT)){ //shortest tower
			pros::lcd::set_text(1, "Shortest tower");
			int encoderValue3 = 50;
			mutex.take(TIMEOUT_MAX);//TEMPORARY VALUE
			while(!((master.get_digital(DIGITAL_R1)) || (master.get_digital(DIGITAL_R2)))){
				if(arm.get_position() > encoderValue3){
					arm.move(-50);
				}
				else{
					arm.move(50);
				}
				if(!((arm.get_position() < 45) && (arm.get_position() > 55))){ //TEMPORARY VALUES
					pros::delay(20);
				}
				else{
					arm.move(0);
				}
			}
			mutex.give();
		}
		pros::delay(20);
	}
}

void opcontrol() {
	pros::Task task1 (drive, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Driving");
	pros::Task task2 (intake, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake");
	pros::Task task3 (anglerMove, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Angler");
	pros::Task task4 (arms, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arms");
	pros::Task task5 (towerScore, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Tower scoring");
}
