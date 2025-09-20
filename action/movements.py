#!/usr/bin/env python

import walk
import stand
import fallManager
import fallRecognition
import stiffnessControl
import stopWalk
import headMove

######################################
#           Motion Variables         #
######################################

X 			= 0.0 # Step size forward (negative to go backwards)
Y 			= 0.0 # Step size left (negative to go right)
Theta 		= 0.0 # Turning angle??
Frequency 	= 0.5 # Frequency of steps (min = 0.0 max = 1.0)

enableFM    = True

isFalling 	= False

jointName   = "HeadYaw" # Can be "HeadYaw" or "HeadPitch"
Angle       = 0.0		# Angle of headMove (HeadPitch: (down_max) 29.5 (up_max) -38.5) (HeadYaw: (left_max) 119.5 (rigth_max) -119.5) 
MaxSpeed    = 0.0		# MaxSpeep of headMove

Position	= "Stand"

######################################
#          Motion Functions          #
######################################

## 	\brief This module is responsable for verifying if the robot has fallen. 
# 	\details To see if the robot has fallen, the sum of the weights of all the feet sensors is computed.
#	\param session Connection with the robot.
def FallRecognition(session):
	global isFalling
	isFalling = fallRecognition.main(session)


## 	\brief This module is responsable for controling robot's stiffness
#	\param session Connection with the robot.
#	\param value Float between 0 (no stiffness) and 1 (max stiffness)
def StiffnessControl(session, value):
	stiffnessControl.main(session, value)


##  \brief This module is responsable for making the robot walk.
#   \param session Connection with the robot.
#   \param X Step size in X axis. (Float between 0.0 and 1.0)
#   \param Y Step size in y axis. (Float between 0.0 and 1.0)
#   \param Theta Step rotation. (Float between 0.0 and 1.0)
#   \param Frequency Step frequency (Float between 0.0 and 1.0)
def Walk(session):
	walk.main(session, X, Y, Theta, Frequency)

## 	\brief This module is responsable for making the robot stand. 
#	\param session Connection with the robot.
def Stand(session):
	stand.main(session, Position)

## 	\brief This module is responsable for disabling the robot's own fallManager.
# 	\details If it doesn't work, it is necessary got go to robot settings and allow deactivation of safety reflexes. 
#	\param session Connection with the robot.
#	\param enable True(enable) or False(disable)
def FallManager(session):
	fallManager.main(session, enableFM)

##  /brief This module is responsable for stoping all of the robot's movements.
#   /param session Connection with the robot.
def StopWalk(session):
	stopWalk.main(session)

##  \brief This module is responsable for moving the robots head.
#   \param session Connection with the robot.
#   \param jointName Name of the head joint. ("HeadYaw" or "HeadPitch")
#   \param Angle Angle (in degrees) that the head is going to move. (Positive values are left and down)
#   \param MaxSpeed Movement speed. (Float between 0.0 and 1.0)
def HeadMove(session):
	headMove.main(session, jointName, Angle, MaxSpeed)

def WaitUntilMoveIsFinished(session):
	motion_service = session.service("ALMotion")
	motion_service.waitUntilMoveIsFinished()

