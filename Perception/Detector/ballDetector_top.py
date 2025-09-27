import cv2
import time
import numpy as np
import logging
import time

import UnBoard.UnBoard as unboard

# Time for robot ball center buffer
# If the ball is lost, robot will pretend the ball is in the last place seen for 4 seconds
buffer_time = 2.0
t0 = 0.0


def main(topCamera):
    global t0

    #####################
    #     Top Camera    #
    #####################

    # Transform botCamera image in grayscale for the cascade search function
    gray = cv2.cvtColor(topCamera, cv2.COLOR_BGR2GRAY)

    # Load the training data
    ball_cascade = cv2.CascadeClassifier('Perception/Cascade/cascade_2024.xml')

    # Detect ball in image
    # ball = ball_cascade.detectMultiScale(gray, 1.2, 5, 0, (20,20), (90,90))
    ball = ball = ball_cascade.detectMultiScale(gray, 1.2, 2, 0, (20, 20), (90, 90))

    # Define ball center (normalized)
    # top left corner of rectangle (x,y)
    # width of rectangle (w)
    # height of rectangle (h)
    for (x, y, w, h) in ball:
        t0 = time.time()

        unboard.seeBallTop = True
        unboard.ballXTop = (x + w / 2) / unboard.width
        unboard.ballYTop = (y + h / 2) / unboard.height

        break  # Robot will only consider ball the first ball in ball vector (Need better solution)

    # If there is no ball, loses ball after buffer time
    if (len(ball) == 0):
        if (time.time() - t0 > buffer_time):
            unboard.seeBallTop = False

            if (unboard.ballXTop > 0.5 and unboard.ballXTop <= 1.0):
                unboard.ballSide = "Right"
            elif (unboard.ballXTop >= 0 and unboard.ballXTop <= 0.5):
                unboard.ballSide = "Left"

            unboard.ballXTop = -1
            unboard.ballYTop = -1