#pragma once
#include <vector>
#include "api.h"
#include "pros/adi.hpp"

inline pros::adi::Pneumatics cl4mp('A', false);
//inline pros::Motor roll1(9);
//inline pros::Motor roll2(10);
//inline pros::Motor hook(11);
inline pros::MotorGroup intake({1, 2, 3});
