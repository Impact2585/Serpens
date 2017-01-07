#include "main.h"
#include "API.h"
#include "systems.h"
#include "ports.h"

void runArmSystem(void) {
    int forwardInput = joystickGetDigital(1, 7, JOY_UP);
    int backwardsInput = joystickGetDigital(1, 7, JOY_RIGHT);
    int lock = joystickGetDigital(1, 7, JOY_LEFT);
    int unlock = joystickGetDigital(1, 7, JOY_DOWN);
    if(forwardInput && !backwardsInput)
        moveArms(50);
    else if(backwardsInput && !forwardInput)
        moveArms(-50);
    else
        moveArms(0);
    if(lock)
        lockArms();
    else if(unlock)
        unlockArms();
}

void initializeArmSystemThread(void) {
    taskRunLoop(runArmSystem, 20);
}

/**
 * Sets the arm motors to speed. Positive moves them forwards and negative moves them backwards.
 *
 *@param speed the speed to seta.
 *
 */
void moveArms(int speed) {
    motorSet(ARM_RIGHT_MOTOR, speed);
    motorSet(ARM_LEFT_MOTOR, -speed);
}

void unlockArms(void) {
    digitalWrite(ARM_PIN, LOW);
}

void lockArms(void) {
    digitalWrite(ARM_PIN, HIGH);
}
