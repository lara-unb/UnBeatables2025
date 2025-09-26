import cv2
import time
import numpy as np
import logging

import unboard

# RGB values for redBallDetection (may need ajustment)

Rmin = 160
Gmin = 0
Bmin = 0

Rmax = 255
Gmax = 110
Bmax = 110

ballCenterBuffer = 150
ballCenterBuffer_cont = 0


def main(botCamera):
    t = time.time()
    global ballCenterBuffer_cont


    ##########################
    #      For Bot Camera    #
    ##########################

    # Red Mask
    mask = cv2.inRange(botCamera, (Bmin, Gmin, Rmin), (Bmax, Gmax, Rmax))

    #Opennig Image
    kernel = np.ones((5, 5), np.uint8)
    closingImg = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

    #Count Pixels
    pixelcount = cv2.countNonZero(closingImg)
    logging.debug(pixelcount)

    maskImg = closingImg.copy()

    if (pixelcount > 700):

        blobDetector = cv2.SimpleBlobDetector_create()

        # Detect blobs.
        blobImg = cv2.bitwise_not(closingImg)
        keypoints = blobDetector.detect(blobImg)

        if (len(keypoints) > 0):
            unboard.seeBallBot = True

            unboard.ballXBot = keypoints[0].pt[0]/unboard.width
            unboard.ballYBot = keypoints[0].pt[1]/unboard.height
            print("by",unboard.ballYBot)
            print("bx", unboard.ballXBot)

            logging.debug((unboard.ballXBot, unboard.ballYBot))

            ballCenterBuffer_cont = 0

        else:
            logging.debug("Not see ball")
            ballCenterBuffer_cont += 1
            if(ballCenterBuffer_cont > ballCenterBuffer):
                unboard.seeBallBot = False
                unboard.ballXBot = -1
                unboard.ballYBot = -1
    else:
        logging.debug("Not see ball")
        ballCenterBuffer_cont += 1
        if(ballCenterBuffer_cont > ballCenterBuffer):
            unboard.seeBallBot = False
            unboard.ballXBot = -1
            unboard.ballYBot = -1 


    ##########################
    #      For Top Camera    #
    ##########################

    # Red Mask
    mask = cv2.inRange(topCamera, (Bmin, Gmin, Rmin), (Bmax, Gmax, Rmax))

    #Opennig Image
    kernel = np.ones((5, 5), np.uint8)
    closingImg = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

    #Count Pixels
    pixelcount = cv2.countNonZero(closingImg)
    logging.debug(pixelcount)

    maskImg = closingImg.copy()

    if (pixelcount > 100):

        blobDetector = cv2.SimpleBlobDetector_create()

        # Detect blobs.
        blobImg = cv2.bitwise_not(closingImg)
        keypoints = blobDetector.detect(blobImg)

        if (len(keypoints) > 0):
            unboard.seeBallTop = True

            unboard.ballXTop = keypoints[0].pt[0]/unboard.width
            unboard.ballYTop = keypoints[0].pt[1]/unboard.height

            logging.debug((unboard.ballXTop, unboard.ballYTop))

            ballCenterBuffer_cont = 0

        else:
            logging.debug("Not see ball")
            ballCenterBuffer_cont += 1
            if(ballCenterBuffer_cont > ballCenterBuffer):
                unboard.seeBallTop = False
                unboard.ballXTop = -1
                unboard.ballYTop = -1
    else:
        logging.debug("Not see ball")
        ballCenterBuffer_cont += 1
        if(ballCenterBuffer_cont > ballCenterBuffer):
            unboard.seeBallTop = False
            unboard.ballXTop = -1
            unboard.ballYTop = -1 
    
    tf = time.time()

    logging.debug(("red ball time", (tf - t)))
