#!/usr/bin/env python

import logging


## 	\brief This module is responsable for verifying if the robot has fallen.
# 	\details To see if the robot has fallen, the sum of the weights of all the feet sensors is computed.
#	\param session Connection with the robot.

def main(session):

    memory_service = session.service("ALMemory")

    # Get The Left Foot Force Sensor Values
    LFsrFL = memory_service.getData(
        "Device/SubDeviceList/LFoot/FSR/FrontLeft/Sensor/Value")
    LFsrFR = memory_service.getData(
        "Device/SubDeviceList/LFoot/FSR/FrontRight/Sensor/Value")
    LFsrBL = memory_service.getData(
        "Device/SubDeviceList/LFoot/FSR/RearLeft/Sensor/Value")
    LFsrBR = memory_service.getData(
        "Device/SubDeviceList/LFoot/FSR/RearRight/Sensor/Value")

    # Get The Right Foot Force Sensor Values
    RFsrFL = memory_service.getData(
        "Device/SubDeviceList/RFoot/FSR/FrontLeft/Sensor/Value")
    RFsrFR = memory_service.getData(
        "Device/SubDeviceList/RFoot/FSR/FrontRight/Sensor/Value")
    RFsrBL = memory_service.getData(
        "Device/SubDeviceList/RFoot/FSR/RearLeft/Sensor/Value")
    RFsrBR = memory_service.getData(
        "Device/SubDeviceList/RFoot/FSR/RearRight/Sensor/Value")

    # Sum the data from all the feet sensors to see if the robot has fallen
    weightL = LFsrFL + LFsrFR + LFsrBL + LFsrBR
    weightR = RFsrFL + RFsrFR + RFsrBL + RFsrBR

    # If the sum of the weights is less than 1Kg, the robot has fallen
    if weightR + weightL < 1.0:
        logging.warning("Robot has fallen.")
        return True

    return False
