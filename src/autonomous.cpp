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

						left_wheels_1.move_absolute(400, 80);
						left_wheels_2.move_absolute(400, 80);
						right_wheels_1.move_absolute(400, 80);
						right_wheels_2.move_absolute(400, 80);

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
						delay(1000);

						left_wheels_1.tare_position();
											left_wheels_2.tare_position();
											right_wheels_1.tare_position();
											right_wheels_2.tare_position();

											left_wheels_1.move_absolute(-400, 80);
											left_wheels_2.move_absolute(-400, 80);
											right_wheels_1.move_absolute(-400, 80);
											right_wheels_2.move_absolute(-400, 80);

											while (!((left_wheels_1.get_position() < -395) && (left_wheels_1.get_position() > -405))) {
											 delay(20);
											}
											while (!((left_wheels_2.get_position() < -395) && (left_wheels_2.get_position() > -405))) {
											delay(20);
										 }
										 while (!((right_wheels_1.get_position() < -395) && (right_wheels_1.get_position() > -405))) {
											delay(20);
										 }
										 while (!((right_wheels_2.get_position() < -395) && (right_wheels_2.get_position() > -405))) {
											delay(20);
										 }

											left_wheels_1.move(0);
											left_wheels_2.move(0);
											right_wheels_1.move(0);
											right_wheels_2.move(0);
											delay(1000);

}

void autonomous() {

movement();

}
