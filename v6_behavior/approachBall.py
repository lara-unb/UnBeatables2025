#!/usr/bin/env python

import mapBehavior
import action
import unboard
import time
import logging

##  \brief Behavior name
behaviorName = "approachBall"

#   Macros
WALK_TIME = 2.0

#   Global variables
firstPass = True
t0 = 0.0


## 	\brief Walk in open loop if ball is between top camera and bot camera
def behaviorAction():
    
    global firstPass
    global t0
    
    # State led
    action.leds.SetRightEyeLeds(action.session, "yellow")

    if(firstPass):
        t0 = time.time()
        firstPass = False

    action.movements.X = 0.9
    action.movements.Y = 0
    action.movements.Walk(action.session)

## 	\brief Transitions to walkBall_bot after time expires
def behaviorTransition():
    global firstPass
    global t0

    t = time.time()

    if(t-t0 > WALK_TIME):
        firstPass = True
        logging.info("walkBall_bot")
        return mapBehavior.walkBall_bot 
    
    return mapBehavior.approachBall

