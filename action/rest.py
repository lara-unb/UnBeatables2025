#!/usr/bin/env python

## 	\brief This module is responsable for making the robot rest.
#	\param session Connection with the robot.

def main(session):

    motion_service = session.service("ALMotion")

    try:
        motion_service.rest()
    except Exception, msg:
        logging.error("Fail rest" + str(msg))
        exit()
