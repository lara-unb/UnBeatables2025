#!/usr/bin/env python

import setLeds

######################################
#           Leds Functions           #
######################################

# Color names suported: white, red, green, blue, yellow, magenta, cyan


## 	\brief Sets both eye leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetEyeLeds(session, color):
	setLeds.main(session, "FaceLeds", color)

## 	\brief Sets rigth eye leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetRightEyeLeds(session, color):
	setLeds.main(session, "RightFaceLeds", color)

## 	\brief Sets left eye leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetLeftEyeLeds(session, color):
	setLeds.main(session, "LeftFaceLeds", color)

## 	\brief Sets chest button leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetChestLeds(session, color):
	setLeds.main(session, "ChestLeds", color)

## 	\brief Sets both feet leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetFeetLeds(session, color):
	setLeds.main(session, "FeetLeds", color)

## 	\brief Sets rigth foot leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetRigthFootLeds(session, color):
	setLeds.main(session, "RightFootLeds", color)

## 	\brief Sets left fot leds.
#	\param session Connection with the robot.
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB
def SetLeftFootLeds(session, color):
	setLeds.main(session, "LeftFootLeds", color)
