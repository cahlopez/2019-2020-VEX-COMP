//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                These functions are called by main.cpp                    //
//                           Make changes here                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
#include "../include/robot.hpp"

RobotClass::RobotClass() :
    master(E_CONTROLLER_MASTER),
    partner(E_CONTROLLER_PARTNER)
{
    Drivetrain = new DrivetrainClass();
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::initialize() {
}

//////////////////////////////////////////////////////////////////////////////
//                                 Disabled                                 //
//               Only runs when the robot is in disabled mode               //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::disabled() {}

//////////////////////////////////////////////////////////////////////////////
//                         Competition-Initialize                           //
//           Only runs when plugged into a comp/field controller            //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::competition_initialize() {}

//////////////////////////////////////////////////////////////////////////////
//                                Autonomous                                //
//              Only runs when the robot is in autonomous mode              //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::autonomous() {}

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::opcontrol() {
    threshold = 15;

    leftVal = (threshold > master.get_analog(ANALOG_LEFT_Y)) ? 0 : master.get_analog(ANALOG_LEFT_Y);
    rightVal = (threshold > master.get_analog(ANALOG_RIGHT_Y)) ? 0 : master.get_analog(ANALOG_RIGHT_Y);
    Drivetrain->update(leftVal, rightVal);
}