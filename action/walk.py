#!/usr/bin/env python

##  \brief This module is responsable for making the robot walk.
#   \param session Connection with the robot.
#   \param X Step size in X axis. (Float between 0.0 and 1.0)
#   \param Y Step size in y axis. (Float between 0.0 and 1.0)
#   \param Theta Step rotation. (Float between 0.0 and 1.0)
#   \param Frequency Step frequency (Float between 0.0 and 1.0)

import logging

def main(session, X, Y, Theta, Frequency):

    motion_service = session.service("ALMotion")
    
    maxStep = 0.08
    # First, wake up.
    motion_service.wakeUp()

    # Disable foot contact protection, if the robot is pulled up, it does not stop walking
    motion_service.setMotionConfig([["ENABLE_FOOT_CONTACT_PROTECTION", False]])

    try:
        motion_service.moveToward(X, Y, Theta, [["Frequency", Frequency], ["MaxStepX", maxStep]])
    except Exception as message:
        logging.error("Fail walk" + str(message))
        exit()
    
