#include "ports.h"
#include "systems.h"
#include "main.h"
#include "API.h"

void runClawSystem(void) {
    if(joystickGetDigital(1, 8, JOY_RIGHT))
        setClawSpeed(1);
    else if(joystickGetDigital(1, 8, JOY_DOWN))
        setClawSpeed(-1);
    else
        setClawSpeed(0);
}

void initializeClawSystemThread(void) {
    taskRunLoop(runClawSystem, 20);
}

void moveClaw(int open) {
    setClawSpeed(open);
    delay(500);
    setClawSpeed(0);
}

void setClawSpeed(int open) {
    motorSet(CLAW_MOTOR_LEFT, open * CLAW_SPEED);
    motorSet(CLAW_MOTOR_RIGHT, open * -CLAW_SPEED);
}
    
