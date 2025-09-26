#!/usr/bin/env python

import logging

## 	\brief This module is responsable for disabling the robot's own fallManager.
# 	\details If it doesn't work, it is necessary got go to robot settings and allow deactivation of safety reflexes.
#	\param session Connection with the robot.
#	\param enable True(enable) or False(disable)

def main(session, enable):
    motion_service = session.service("ALMotion")

    try:
        motion_service.setFallManagerEnabled(enable)
    except Exception, msg:
        logging.error("Fail to disable FallManager" + str(msg))
