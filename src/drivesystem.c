/*
 * drivesystem.c
 */
#include "ports.h"
#include "systems.h"
#include "main.h"
#include "API.h"
#include <stdlib.h>


//true speed array
const int TrueSpeed[128] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
 25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
 28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
 33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
 37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
 41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
 46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
 52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
 61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
 71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
 80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
 88, 89, 89, 90, 90,127,127,127
};

static struct driveSystem drivetrain;

//the task to be run
void runDriveSystem(void) {
    drivetrain.yAxis = joystickGetAnalog(1, 3);
    drivetrain.xAxis = joystickGetAnalog(1, 1);
    int toggleDriveMode = joystickGetDigital(1, 8, JOY_LEFT);

	if(toggleDriveMode && !drivetrain.prevToggle) {
		drivetrain.reversedMode ^= 1;
	}

	setDriveTrainDeadZone();
	setReversed();
	calculateDriveSystemSpeed();

	motorDriveControlRight(drivetrain.rightSpeed);
	motorDriveControlLeft(drivetrain.leftSpeed);
	drivetrain.prevToggle = toggleDriveMode;
}


//the drive task thread
void initializeDriveSystemThread(void) {
	initializeDriveSystem(&drivetrain);
    taskRunLoop(runDriveSystem, 20);
}


//initialize the drive system struct pointer
void initializeDriveSystem(struct driveSystem* drivetrain) {
	drivetrain->xAxis = 0;
	drivetrain->yAxis = 0;
	drivetrain->reversedMode = 0;
	drivetrain->prevToggle = 0;
	drivetrain->leftSpeed = 0;
	drivetrain->rightSpeed = 0;
}

//reverses the axis values if the drivetrain is in reversed mode
void setReversed(void) {
	if(drivetrain.reversedMode) {
		drivetrain.yAxis *= -1;
	}
}

//calculates the left and right speeds of the drivetrain
void calculateDriveSystemSpeed(void) {
	int right = drivetrain.yAxis - drivetrain.xAxis;
	int left = drivetrain.yAxis + drivetrain.xAxis;
	drivetrain.rightSpeed = sign(right) * TrueSpeed[abs(right) > 127 ? 127 : abs(right)];
	drivetrain.leftSpeed = sign(left) * TrueSpeed[abs(left) > 127 ? 127 : abs(left)];
}

//sets the xAxis and yAxis values to 0 if the absolute value is below 15
void setDriveTrainDeadZone(void) {
	if(abs(drivetrain.xAxis) < DEADZONE)
		drivetrain.xAxis = 0;
	if(abs(drivetrain.yAxis) < DEADZONE)
		drivetrain.yAxis = 0;
}

//set the speed of the left drivetrain motors
void motorDriveControlLeft(int speed) {
	motorSet( MOTOR_DRIVE_LEFT_FRONT, speed);
	motorSet( MOTOR_DRIVE_LEFT_BEHIND, speed);
}

//set the speed of the right drivetrain motors
void motorDriveControlRight(int speed) {
	motorSet( MOTOR_DRIVE_RIGHT_FRONT, speed);
	motorSet( MOTOR_DRIVE_RIGHT_BEHIND, speed);
}

