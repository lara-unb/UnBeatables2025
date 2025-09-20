#!/usr/bin/env python

## 	\brief This module is responsable for controling robot's stiffness
#	\param session Connection with the robot.
#	\param value Float between 0 (no stiffness) and 1 (max stiffness)

def main(session, value):

	motion_service  = session.service("ALMotion")
	motion_service.setStiffnesses("Body", value)
	