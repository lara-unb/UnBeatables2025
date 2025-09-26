#!/usr/bin/env python

## 	\brief This module is for setting robot's leds
#	\details Color names suported: white, red, green, blue, yellow, magenta, cyan
#	\param session Connection with the robot.
#	\param name Led or group name
#	\param color Name of the color or RGB in hexadecimal 0x00RRGGBB

def main(session, name, color):
	
	leds_service = session.service("ALLeds")
	leds_service.fadeRGB(name, color, 0.1)
