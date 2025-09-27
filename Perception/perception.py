import logging
import random
import time

import numpy as np
import vision_definitions

import Detector.ballDetector_bot as ballDetector_bot
import Detector.ballDetector_bot as ballDetector_top
from Libs.Logs import logs


class Perception:
    def __init__(self, session):
        self.session = session
        self.isRunning = True

        self.video_service = self.session.service("ALVideoDevice")

        self.resolution = vision_definitions.kQVGA
        self.colorSpace = vision_definitions.kBGRColorSpace
        self.fps = 5

        self.topCamera = self.video_service.subscribeCamera(
            "python_top" + str(random.randint(1, 10)), 0, self.resolution, self.colorSpace,
            self.fps)
        self.botCamera = self.video_service.subscribeCamera(
            "python_bot" + str(random.randint(1, 10)), 1, self.resolution, self.colorSpace,
            self.fps)

    def run(self):
        logs.logger_perception.info("Running Perception")
        while self.isRunning:
            self.__process()
            time.sleep(0.001)

    def close(self):
        logs.logger_perception.info("Closing Perception")
        self.isRunning = False
        self.video_service.unsubscribe(self.topCamera)
        self.video_service.unsubscribe(self.botCamera)

    def alImage2npImage(self, image):
        imgWidth = image[0]
        imgHeight = image[1]
        imgChannels = image[2]
        npImg = np.reshape(image[6], (imgHeight, imgWidth, imgChannels))
        return npImg

    def __process(self):
        logs.logger_perception.info("Processing Perception")
        topNAOImage = self.video_service.getImageRemote(self.topCamera)
        if (topNAOImage == None):
            logs.logger_perception.error("No topImage")

        botNAOImage = self.video_service.getImageRemote(self.botCamera)
        if (botNAOImage == None):
            logs.logger_perception.error("No botImage")

        topImage = self.alImage2npImage(topNAOImage)
        botImage = self.alImage2npImage(botNAOImage)

        ballDetector_bot.main(botImage)
        ballDetector_top.main(topImage)

