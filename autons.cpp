#include "main.h" // IWYU pragma: keep
#include "subsystems.hpp"


// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

// Constants
void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

// grab mobile goal, score preload, touch ladder
  /* tarique tip: go for the side w/ less rings! (bc most ppl wil be on
     the other side w/ more rings to score)
  */
void winPoint() {
  //STARTING POSITION: facing backwards with clamp towards mobile goal (all driving movement swapped/backwards)
  
  //prep to get mobile goal
  cl4mp.retract();  

  //drive to mobile goal
  chassis.pid_drive_set(-33_in, DRIVE_SPEED);
  chassis.pid_wait();

  //use clamp to get mobile goal
  cl4mp.extend();

  //run intake to score preload
  ouroboros.move_voltage(12000);  
  pros::delay(500); //TEST TO SEE HOW LONG THIS WAITS --- ENSURE ENOUGH TIME TO SCORE RING

  //stop intake
  ouroboros.move_voltage(0);

  //let go of mobile goal
  cl4mp.retract();  

  //move back a little
  chassis.pid_drive_set(11_in, DRIVE_SPEED);
  chassis.pid_wait();

  //turn towards ladder corner 
  chassis.pid_turn_set(-60_deg, TURN_SPEED);
  chassis.pid_wait();

  //move & touch ladder
  chassis.pid_drive_set(-30_in, DRIVE_SPEED);
  chassis.pid_wait();

}

// higher focus on scoring
void normal(){
  // move 27 inches towards the goal.
  chassis.pid_drive_set(27_in, DRIVE_SPEED);

  //clamp the stake into the robot
  cl4mp.extend();

  //run intake to score preload
  ouroboros.move_voltage(12000);
  pros::delay(500); //TEST TO SEE HOW LONG THIS WAITS --- ENSURE ENOUGH TIME TO SCORE RING
  
  //stop intake
  ouroboros.move_voltage(0);

  //let go of mobile goal
  cl4mp.retract();  

  //move back a little
  chassis.pid_drive_set(11_in, DRIVE_SPEED);
  chassis.pid_wait();

  // turn slight right towards the other rings
  chassis.pid_turn_set(35_deg, TURN_SPEED);

  //move forward towards 24 inches to the rings.
  chassis.pid_drive_set(24_in, DRIVE_SPEED);

  //turn 90 degrees left around to get the rings
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_drive_set(6_in, DRIVE_SPEED);
  
  //run intake to score the red/blue ring.
  //depend where you start it.
  ouroboros.move_voltage(12000);
  pros::delay(500); //TEST TO SEE HOW LONG THIS WAITS --- ENSURE ENOUGH TIME TO SCORE RING
  
  //stop intake
  ouroboros.move_voltage(0);

  //Once you take the red or blue ring, go to the other rings
  //in front of the previous ring picked up onto the intake.
  chassis.pid_drive_set(12in, DRIVE_SPEED);

  //run intake to score the red/blue ring.
  //depend where you start it.
  ouroboros.move_voltage(12000);
  pros::delay(500); //TEST TO SEE HOW LONG THIS WAITS --- ENSURE ENOUGH TIME TO SCORE RING
  
  //stop intake
  ouroboros.move_voltage(0);

  //Move back and put the rings that were taken into the stake.
  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_drive_set(-90_in, TURN_SPEED);
  chassis.pid_drive_set(24_in, DRIVE_SPEED);

  //Clamp the stake onto the robot and put the rings onto the stake.
  cl4mp.extend();

  //run intake to score preload
  ouroboros.move_voltage(12000);
  pros::delay(500); //TEST TO SEE HOW LONG THIS WAITS --- ENSURE ENOUGH TIME TO SCORE RING
  
  //stop intake
  ouroboros.move_voltage(0);

  //Bring the stake onto the side.
  chassis.pid_drive_set(27_in, DRIVE_SPEED);

  //let go of mobile goal
  cl4mp.retract();

}

/* 
   1. score red preload (onto alliance stake or mobile goal) 
   2. score all red rings onto stakes
	    put mobile goals into corners
   3. score blue rings on top, 1 per stake
*/
void skills() {
  chassis.pid_drive_set(-15_in, DRIVE_SPEED);
  chassis.pid_wait();

  ouroboros.move_voltage(12000);
  pros::delay(400);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();
}
