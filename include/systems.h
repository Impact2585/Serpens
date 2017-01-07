

/**
 * Drive Functions and constants
 */

#define LEFT_JOYSTICK 1
#define RIGHT_JOYSTICK 2

#define HORIZONTAL 1
#define VERTICAL 2

#define DEADZONE 15

/**
 * toggle button: 8 UP.
 */

 struct driveSystem {
    int xAxis;
    int yAxis;
    int reversedMode;
    int prevToggle;
    int leftSpeed;
    int rightSpeed;
};

void motorDriveControlLeft(int speed);
void motorDriveControlRight(int speed);
void setDriveTrainDeadZone(void);
void calculateDriveSystemSpeed(void);
void setReversed(void);
void initializeDriveSystem(struct driveSystem* drivetrain);

void initializeDriveSystemThread(void);

/**
 * Shooter functions and constants.
 */
#define DEFAULT_SHOOTER_SPEED 100
struct shootInfo {
    int forwardShoot;
    int backShoot;
    int shouldShoot;
    int isLocked;
    int releaseLock;
    int lock;
    int unlock;
};

void releaseLock(void);
void setShootSpeed(int speed);
void getShooterInput();
void initializeShootSystemThread(void);
void primeForShooting(void);

/**
 * Claw functions and constants.
 */

 #define CLAW_SPEED 40
 void setClawSpeed(int open);
 void moveClaw(int open);
 void initializeClawSystemThread();

 /**
  * Arm functions and constants.
  */

  void initializeArmSystemThread(void);
  void moveArms(int speed);
  void lockArms(void);
  void unlockArms(void);
