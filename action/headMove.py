#!/usr/bin/env python

import math

##  \brief This module is responsable for moving the robots head.
#   \param session Connection with the robot.
#   \param jointName Name of the head joint. ("HeadYaw" or "HeadPitch")
#   \param Angle Angle (in degrees) that the head is going to move. (Positive values are left and down)
#   \param fractionMaxSpeed Movement speed. (Float between 0.0 and 1.0)

def main(session, jointName, Angle, fractionMaxSpeed):

    motion_service = session.service("ALMotion")
    Angle = (math.pi * Angle) / 180

    try:
        motion_service.setAngles(jointName, Angle, fractionMaxSpeed)
    except Exception, msg:
        logging.error("Fail head motion" + str(msg))
        exit()
