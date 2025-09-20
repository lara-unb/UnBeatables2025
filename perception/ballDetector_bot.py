import cv2
import time
import numpy as np
import logging
import time

import unboard


# Time for robot ball center buffer
# If the ball is lost, robot will pretend the ball is in the last place seen for 4 seconds
buffer_time = 4.0
t0 = 0.0


def main(botCamera):
	global t0

	#####################
	#     Bot Camera    #
	#####################

	# Transform botCamera image in grayscale for the cascade search function
	gray = cv2.cvtColor(botCamera, cv2.COLOR_BGR2GRAY)
	# Load the training data
	ball_cascade = cv2.CascadeClassifier('v6_perception/cascade_PB.xml')
	
	# Detect ball in image
	ball = ball = ball_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=5, minSize=(10, 10))
	#ball = ball_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=2, minSize=(10, 10))
 	

	# Define ball center (normalized)
	# top left corner of rectangle (x,y)
	# width of rectangle (w)
	# height of rectangle (h)
	for (x,y,w,h) in ball:
		t0 = time.time()

		unboard.seeBallBot = True
		unboard.ballXBot = (x+w/2)/unboard.width
		unboard.ballYBot = (y+h/2)/unboard.height
		

		break # Robot will only consider ball the first ball in ball vector (Need better solution) 

	# If there is no ball, loses ball after buffer time
	if (len(ball) == 0):
		# print("NAO ENCONTRO A BOLA")
		if(time.time()-t0 > buffer_time):
			unboard.seeBallBot = False
			if(unboard.ballXBot > 0.5 and unboard.ballXBot <=1.0):
				unboard.ballSide = "Right"
			elif(unboard.ballXBot >=0 and unboard.ballXBot <= 0.5):
				unboard.ballSide = "Left"
			unboard.ballXBot = -1
			unboard.ballYBot = -1

	
