#!/usr/bin/env python

import mapBehavior
import action
import unboard
import time
import logging

## \brief Behavior name
behaviorName = "lookForBall"

# Macros
TURN_TIME = 18.0

# Global variables
t0 = 0.0
firstPass = True


## 	\brief Behavior that turns to look for ball
def behaviorAction():
    global firstPass
    global t0
    
    # print("BALLY: ", unboard.ballYBot)

    if(firstPass):
        t0 = time.time()
        firstPass = False

    # State led
    action.leds.SetRightEyeLeds(action.session, "magenta")

    # Adjust head
    action.movements.jointName = "HeadYaw"
    action.movements.Angle = 0.0
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    action.movements.jointName = "HeadPitch"
    action.movements.Angle = 29.0
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    if(unboard.ballSide == "Left"):
        sign = 1
    else:
        sign = -1


    action.movements.X = 0.5
    action.movements.Y = 0.0
    action.movements.Theta = 0.0		
    #action.movements.Theta = sign*0.5
    action.movements.Walk(action.session)

## \brief If ball is seen in bot camera, transitions to walkBall_bot <br>
#         If ball is seen in top camera, transitions to walkBall_top <br>
#         TODO If time expires transitions to walkRandom

def behaviorTransition():
    global firstPasss
    global t0

    t = time.time()

    if(unboard.seeBallBot):
        firstPass = True
        action.movements.Theta = 0.0
        logging.info("WalkBall_bot")
        return mapBehavior.walkBall_bot

    elif(unboard.seeBallTop):
        firstPass = True
        action.movements.Theta = 0.0
        logging.info("WalkBall_top")
        return mapBehavior.walkBall_top

    if(t-t0 > TURN_TIME):
        firstPass = True
        return mapBehavior.approachBall
    

    return mapBehavior.lookForBall
