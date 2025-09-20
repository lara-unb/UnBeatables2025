#!/usr/bin/env python

import qi
import vision_definitions
import numpy as np
import cv2
import time
import random
import os
import logging

import redBallDetector
import ballDetector_bot
import ballDetector_top
import unboard

session = qi.Session()


def main():

    # Get the service ALVideoDevice.
    video_service = session.service("ALVideoDevice")

    # Register a Generic Video Module
    resolution = vision_definitions.kQVGA
    colorSpace = vision_definitions.kBGRColorSpace
    fps = 5

    topCamera = video_service.subscribeCamera(
        "python_top" + str(random.randint(1, 10)), 0, resolution, colorSpace,
        fps)
    botCamera = video_service.subscribeCamera(
        "python_bot" + str(random.randint(1, 10)), 1, resolution, colorSpace,
        fps)

    # Get ALImages of top camera and bottom camera
    while (True):

        topNAOImage = video_service.getImageRemote(topCamera)
        if (topNAOImage == None):
            logging.error("No topImage")

        botNAOImage = video_service.getImageRemote(botCamera)
        if (botNAOImage == None):
            logging.error("No botImage")


        topImage = alImage2npImage(topNAOImage)
        botImage = alImage2npImage(botNAOImage)

        # redBallDetector.main(botImage)
        ballDetector_bot.main(botImage)
        # print("balldetector_bot")
        ballDetector_top.main(topImage)


    video_service.unsubscribe(topCamera)
    video_service.unsubscribe(botCamera)


def alImage2npImage(image):

    imgWidth = image[0]
    imgHeight = image[1]
    imgChannels = image[2]
    npImg = np.reshape(image[6], (imgHeight, imgWidth, imgChannels))
    # print("npImg:", npImg)
    return npImg
