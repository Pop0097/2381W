#include "main.h"
#include <math.h>
#include "motors.h"
#include "adi.h"
#include "pid.h"

using namespace pros;

PID pid2 = PID(0.1, 75, -75, 0.1, 0.01, 0.5);//constructs PID object
// void ultrasonic(void*) {

// 	while (true) {
// 		while (ultra_left.get_value() > 100 && ultra_right.get_value() > 100) {
//     // Move forward until the robot is 100 cm from a solid object
// 		angler.move(127);
//     pros::delay(50);
//   }
// }
//
// }

void movement() {

			left_wheels_1.tare_position();
		  left_wheels_2.tare_position();
		  right_wheels_1.tare_position();
		  right_wheels_2.tare_position();

	  intake_left.move(-100);
	  intake_right.move(-100);
		delay(100);

	  left_wheels_1.move_absolute(-3350, 50);
	  left_wheels_2.move_absolute(-3350, 50);
	  right_wheels_1.move_absolute(-3350, 50);
	  right_wheels_2.move_absolute(-3350, 50);

	  while (!((left_wheels_1.get_position() < -3345) && (left_wheels_1.get_position() > -3455))) {
	   delay(20);
	  }
		while (!((left_wheels_2.get_position() < -3345) && (left_wheels_2.get_position() > -3455))) {
		delay(20);
	 }
	 while (!((right_wheels_1.get_position() < -3345) && (right_wheels_1.get_position() > -3455))) {
		delay(20);
	 }
	 while (!((right_wheels_2.get_position() < -3345) && (right_wheels_2.get_position() > -3455))) {
		delay(20);
	 }

	  left_wheels_1.move(0);
	  left_wheels_2.move(0);
	  right_wheels_1.move(0);
	  right_wheels_2.move(0);
		intake_left.move(0);
		intake_right.move(0);
		delay(100);
		std::string d1 = std::to_string(left_wheels_1.get_position());
		lcd::set_text(0, d1);
		std::string d2 = std::to_string(right_wheels_1.get_position());
		lcd::set_text(1, d2);
		std::string d3 = std::to_string(left_wheels_2.get_position());
		lcd::set_text(2, d3);
		std::string d4 = std::to_string(right_wheels_2.get_position());
		lcd::set_text(3, d4);

	//Code to rotate ccw 90º

	left_wheels_1.tare_position();
	left_wheels_2.tare_position();
	right_wheels_1.tare_position();
	right_wheels_2.tare_position();

	lcd::set_text(4, "Fuck!");

	left_wheels_1.move_absolute(-160, 60);
	left_wheels_2.move_absolute(-160, 60);
	right_wheels_1.move_absolute(140, 60);
	right_wheels_2.move_absolute(140, 60);
	while (!((left_wheels_1.get_position() < -155) && (left_wheels_1.get_position() > -165))) {
	 delay(20);
	}
	while (!((left_wheels_2.get_position() < -155) && (left_wheels_2.get_position() > -165))) {
	 delay(20);
	}
	while (!((right_wheels_1.get_position() < 145) && (right_wheels_1.get_position() > 135))) {
	 delay(20);
	}
	while (!((right_wheels_2.get_position() < 145) && (right_wheels_2.get_position() > 135))) {
	 delay(20);
	}

	left_wheels_1.move(0);
	left_wheels_2.move(0);
	right_wheels_1.move(0);
	right_wheels_2.move(0);
	intake_left.move(0);
	intake_right.move(0);
	delay(50);

	left_wheels_1.tare_position();
	left_wheels_2.tare_position();
	right_wheels_1.tare_position();
	right_wheels_2.tare_position();

left_wheels_1.move_absolute(-250, 50);
left_wheels_2.move_absolute(-250, 50);
right_wheels_1.move_absolute(-250, 50);
right_wheels_2.move_absolute(-250, 50);

while (!((left_wheels_1.get_position() < -245) && (left_wheels_1.get_position() > -255))) {
 delay(20);
}
while (!((left_wheels_2.get_position() < -245) && (left_wheels_2.get_position() > -255))) {
delay(20);
}
while (!((right_wheels_1.get_position() < -245) && (right_wheels_1.get_position() > -255))) {
delay(20);
}
while (!((right_wheels_2.get_position() < -245) && (right_wheels_2.get_position() > -255))) {
delay(20);
}

left_wheels_1.move(0);
left_wheels_2.move(0);
right_wheels_1.move(0);
right_wheels_2.move(0);

	  //Code to place the cubes in the goal zone
		angler.tare_position();
	  angler.move_absolute(300, 100);
	  while (!((angler.get_position() < 305) && (angler.get_position() > 295))) {
	   delay(20);
	  }

	  angler.move_absolute(450, 75);
	  while (!((angler.get_position() < 455) && (angler.get_position() > 445))) {
	   delay(20);
	  }

	  angler.move_absolute(550, 50);
	  while (!((angler.get_position() < 555) && (angler.get_position() > 545))) {
	   delay(20);
	  }

	  angler.move(0);

		left_wheels_1.tare_position();
		left_wheels_2.tare_position();
		right_wheels_1.tare_position();
		right_wheels_2.tare_position();

	  //backs away
	  left_wheels_1.move_absolute(400, 80);
	  left_wheels_2.move_absolute(400, 80);
	  right_wheels_1.move_absolute(400, 80);
	  right_wheels_2.move_absolute(400, 80);
	   delay(50);

		 while (!((left_wheels_1.get_position() < 405) && (left_wheels_1.get_position() > 395))) {
			delay(20);
		 }
		 while (!((left_wheels_2.get_position() < 405) && (left_wheels_2.get_position() > 395))) {
		 delay(20);
		}
		while (!((right_wheels_1.get_position() < 405) && (right_wheels_1.get_position() > 395))) {
		 delay(20);
		}
		while (!((right_wheels_2.get_position() < 405) && (right_wheels_2.get_position() > 395))) {
		 delay(20);
		}

	  left_wheels_1.move(0);
	  left_wheels_2.move(0);
	  right_wheels_1.move(0);
	  right_wheels_2.move(0);

		//...turn
		//...move to tower
		//...cube and tower (one motion)

		//...turn
		//...move to tower
		//...cube and tower (one motion)
		//27 points!

}

void autonomous() {

movement();

}
