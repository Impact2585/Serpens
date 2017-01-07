/*
 * shootersystem.c
 */
#include "main.h"
#include "systems.h"
#include "ports.h"
static struct shootInfo shooter;
//the lift task to run
void runShootTask(void) {
	//grabs input for shooter
	getShooterInput();

	//moves catapult backwards and locks it if button is pressed and the shooter isn't already locked
	if(shooter.shouldShoot && !shooter.isLocked) {
		primeForShooting();
		shooter.isLocked = 1;
	} else if(shooter.releaseLock && shooter.isLocked) {
		//releases lock and sets isLocked to 0
		releaseLock();
		shooter.isLocked = 0;
	} else {
		//manual control of the shooter
		if(shooter.forwardShoot) {
			setShootSpeed(-DEFAULT_SHOOTER_SPEED);
		} else if(shooter.backShoot) {
			setShootSpeed(DEFAULT_SHOOTER_SPEED);
		} else {
			setShootSpeed(0);
		}
		
		if(shooter.lock)
			digitalWrite(PNEUMATICS_PIN, HIGH);
		else if(shooter.unlock)
			digitalWrite(PNEUMATICS_PIN, LOW);
	}
}

/**
 * Initializes the shooter struct
 */
void initShooter(void) {
    shooter.forwardShoot = 0;
    shooter.backShoot = 0;
    shooter.shouldShoot = 0;
    shooter.isLocked = 0;
    shooter.releaseLock = 0;
    shooter.lock = 0;
    shooter.unlock = 0;
}

//moves the catapult backwards and locks it in place with pneumatics
void primeForShooting(void) {
	setShootSpeed(-DEFAULT_SHOOTER_SPEED);
	delay(5000);
	//let Jesus and rubber bands do the rest
	setShootSpeed(0);
	//lock the pneumatics
	digitalWrite(PNEUMATICS_PIN, HIGH);
}

//get input for the shooter
void getShooterInput(void) {
	shooter.forwardShoot = joystickGetDigital(1, 6, JOY_UP);
	shooter.backShoot = joystickGetDigital(1, 6, JOY_DOWN);
	shooter.releaseLock = joystickGetDigital(1, 8, JOY_UP);
	shooter.shouldShoot = joystickGetDigital(1, 8, JOY_RIGHT);
	shooter.lock = joystickGetDigital(1, 5, JOY_DOWN);
	shooter.unlock = joystickGetDigital(1, 5, JOY_UP);
}

//release pneumatic lock
void releaseLock(void) {
	digitalWrite(PNEUMATICS_PIN, LOW);
	setShootSpeed(DEFAULT_SHOOTER_SPEED);
    delay(500);
	setShootSpeed(0);
}

//the shoot task thread
void initializeShootSystemThread(void) {
    initShooter();
    taskRunLoop(runShootTask, 20);
}

//sets the lift speeds
void setShootSpeed(int speed) {
	motorSet(SHOOT_MOTOR_1, speed);
    motorSet(SHOOT_MOTOR_2, -speed);
}

