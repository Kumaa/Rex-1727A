/*
 * drive.c
 *
 *  Created on: Sep 24, 2016
 *      Author: Tomer
 */

#include "main.h"

//the left  drive stuffs
#define     MOTORLF     2
#define     MOTORLB     10


//the lift stuffs
#define     MOTORLIFTR1 5
#define		MOTORLIFTR2 6
#define		MOTORLIFTL1	3
#define		MOTORLIFTL2	4

//the right drive stuffs
#define     MOTORRF     1
#define     MOTORRB     9


void
simpleLift()
{
    int  drive_lift = 0;
    int  vex_Btn8U = joystickGetDigital( 1, 8, JOY_UP );
    int  vex_Btn8D = joystickGetDigital( 1, 8, JOY_DOWN );

    // get control value
    if( vex_Btn8U )
        drive_lift = 127;
    else
    if( vex_Btn8D )
        drive_lift = -127;
    else
        drive_lift = 0;

    // set the motor
    motorSet( MOTORLIFTL1, drive_lift );
    motorSet( MOTORLIFTL2, drive_lift );
    motorSet( MOTORLIFTR1, drive_lift );
    motorSet( MOTORLIFTR2, drive_lift );
}



void
simpleDrive()
{
    long drive_l;
    long drive_linear;
    long drive_shift;
    long drive_rotate;
    long drive_r;

    // Get the joystick values
    int  vex_ch1 = joystickGetAnalog( 1, 1 );
    int  vex_ch3 = joystickGetAnalog( 1, 3 );
    int  vex_ch4 = joystickGetAnalog( 1, 4 );

    // create forward and turn variables
    // use a deadband of 10
    if( abs( vex_ch3 ) > 10 )
        drive_linear = vex_ch3;
    else
    	drive_linear = 0;

    if( abs( vex_ch4 ) > 10 )
    	drive_shift = vex_ch3;
    else
    	drive_shift = 0;

    if( abs( vex_ch1 ) > 10)
    	drive_rotate = vex_ch1;
    else
    	drive_rotate = vex_ch1;

    int rf = drive_linear - drive_shift - drive_rotate;

    int rb = drive_linear + drive_shift - drive_rotate;

    int lf = drive_linear + drive_shift + drive_rotate;

    int lb = drive_linear - drive_shift + drive_rotate;
    // Set drive
  //  drive_l = forward + turn;
    //drive_r = forward - turn;

    // normalize drive so max is 127 if any drive is over 127
  /*  int max = abs(drive_l);
    if (abs(drive_r)  > max)
        max = abs(drive_r);
    if (max>127) {
        drive_l = 127 * drive_l / max;
        drive_r = 127 * drive_r  / max;
    }
*/
    // Send to motors
    // left drive
    motorSet( MOTORLF, -lf);
    motorSet( MOTORLB, -lb);

    // right drive
    motorSet( MOTORRF, -rf);
    motorSet( MOTORRB, -rb);
}

/*-----------------------------------------------------------------------------*/
/*  operator control function                                                  */
/*-----------------------------------------------------------------------------*/

void operatorControl() {

    while (1) {
        // arcade drive
        simpleDrive();

        // Simple one motor lift
        simpleLift();

        // Don't hog cpu
        delay(20);
    }
}
