#!/usr/bin/env python

##  \brief This module is responsable to make the robot stop.
#   \param session Connection with the robot.


def main(session):
    motion_service = session.service("ALMotion")


    try:
        motion_service.stopMove()
    except Exception, msg:
        logging.error("Couldn't stop walking" + str(msg))
        exit()
