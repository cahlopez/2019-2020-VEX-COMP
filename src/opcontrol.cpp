#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	Controller master(E_CONTROLLER_MASTER);

	_trayPIDArg* trayPIDPtr = new _trayPIDArg();
	Task trayTask(trayPID, trayPIDPtr, "TrayPIDTask");

	_armPIDArg* armPIDPtr = new _armPIDArg();
	Task armTask(armPID, armPIDPtr, "ArmPIDTask");
	
	trayMotor.tare_position();
	armMotor.tare_position();

	// Variable decloration and initialization
	int threshold = 15;

	while (true) {
		// Control for the left side of the drive trainß
		if(abs(master.get_analog(ANALOG_LEFT_Y)) >= threshold) {
			frontLeftMotor.move(master.get_analog(ANALOG_LEFT_Y));
			backLeftMotor.move(master.get_analog(ANALOG_LEFT_Y));
		} else {
			frontLeftMotor.move(0);	
			backLeftMotor.move(0);
		}

		// Control for the right side of the drive train
		if(abs(master.get_analog(ANALOG_RIGHT_Y)) >= threshold) {
			frontRightMotor.move(master.get_analog(ANALOG_RIGHT_Y));
			backRightMotor.move(master.get_analog(ANALOG_RIGHT_Y));
		} else {
			frontRightMotor.move(0);
			backRightMotor.move(0);
		}

		// Tray auto place macro
		if(master.get_digital(DIGITAL_A)) {
			while(master.get_digital(DIGITAL_A)) delay(20);

			if(trayPIDPtr->trayPIDRunning) {
				trayPIDPtr->trayPIDRunning = false;
			} else {
				trayPIDPtr->trayPIDRunning = true;
			}
		}

		if(master.get_digital(DIGITAL_B)) {
			while(master.get_digital(DIGITAL_B)) delay(20);

			trayPIDPtr->trayPIDRunning = true;

			if(trayPIDPtr->inTarget <= 10) {
				trayPIDPtr->inTarget = 5500;
				trayPIDPtr->powerLimit = 60;
			} else if(trayPIDPtr->inTarget >= 1600) {
				trayPIDPtr->inTarget = 10;
				trayPIDPtr->powerLimit = 80;
			}
		}

		if(trayPIDPtr->powerLimit == 80 && trayMotor.get_position() <= 20) {
			trayPIDPtr->trayPIDRunning = false;
		}

		// Tray manual control
		if(master.get_digital(DIGITAL_R1) == 1) {
			trayPIDPtr->trayPIDRunning = false;
			trayMotor.move(80);
		} else if(master.get_digital(DIGITAL_R2) == 1) {
			trayPIDPtr->trayPIDRunning = false;
			trayMotor.move(-90);
		} else {
			trayMotor.move(0);
		}

		// Arm control
		if(master.get_digital(DIGITAL_X) == 1) {
			armPIDPtr->armPIDRunning = false;
			armMotor.move(127);
			armPIDPtr->inTarget = armMotor.get_position();
		} else if(master.get_digital(DIGITAL_Y) == 1) {
			armPIDPtr->armPIDRunning = false;
			armMotor.move(-127);
			armPIDPtr->inTarget = armMotor.get_position();
		} else {
			if(armMotor.get_position() >= 60) {
				armPIDPtr->armPIDRunning = true;
			} else {
				armPIDPtr->armPIDRunning = false;
				armMotor.move(0);
			}
		}

		// Intake control
		if(master.get_digital(DIGITAL_L1) == 1) {
			leftIntake.move(127);
			rightIntake.move(127);
		} else if(master.get_digital(DIGITAL_L2) == 1) {
			leftIntake.move(-127);
			rightIntake.move(-127);
		} else {
			leftIntake.move(0);
			rightIntake.move(0);
		}

		// Delay task to stop CPU hogging
		delay(20);
		cout << armMotor.get_position() << endl;
	}
}
