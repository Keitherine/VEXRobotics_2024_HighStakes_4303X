#pragma once
#include "EZ-Template/drive/drive.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"

inline ez::Drive chassis
(
    {-5, -7, 13}, // Left Motors, reversed
    {14, -15, 16}, // Right Motors
    //top motors are flipped (13 & 15)

    2, // IMU Port
    3.25,  // Wheel Diameter
    600 // Wheel RPM
);   
inline pros::adi::Pneumatics cl4mp('A', false);
inline pros::Motor ouroboros(10);
//inline pros::MotorGroup ouroboros({-10, 19});

inline pros::Motor ladyBrown(19); //check/change port
inline pros::adi::Pneumatics doink('B', false); //check/change port
