#include "main.h"
#include "EZ-Template/util.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "subsystems.hpp"

ez::Drive chassis
(
    {5, 7, -13}, // Left Motors
    {-14, 15, -16}, // Right Motors, reversed
      //14 is wacky - vincent
    //top motors are flipped (13 & 15)

    7, // IMU Port
    3.25,  // Wheel Diameter
    600 // Wheel RPM
);   

void initialize() {
  pros::delay(500);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  default_constants(); // edit from autons.cpp

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector
  ez::as::auton_selector.autons_add({
     // Auton("Auton 1\n\nDrive forward and come back.", auton1),
     // Auton("Auton 2\n\n", auton2),
     // Auton("Auton 3\n\n", auton3),
     // Auton("Match Auton\n\n", matchAuton),
     // Auton("Skills Auton\n\n", skills),
  });

  // Initialize
  chassis.initialize();
  ez::as::initialize();
}

void disabled() {}
void competition_initialize() {}

void autonomous() {
  chassis.pid_targets_reset();                
  chassis.drive_imu_reset();                  
  chassis.drive_sensor_reset();               
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); 
  ez::as::auton_selector.selected_auton_call();
}

void opcontrol() {
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  while (true) {
    chassis.opcontrol_tank();

    // define functions in another seperate cpp file (K's was 'helpers.cpp'), then just dump 'em all here
    // OR make a class for each subsystem seperately

    //toggle, clamp-- any of the letter buttons (A, X, Y, B)
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) || master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) || master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) || master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
    {
      cl4mp.toggle();
    }

    //hold, intake-- intake r1, outtake l1
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
      intake.move_voltage(12000);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
      intake.move_voltage(-12000);
    }
    else 
    {
      intake.move_voltage(0);
    }

    //make inline macros here

    pros::delay(ez::util::DELAY_TIME); 
  }
}
