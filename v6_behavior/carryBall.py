#!/usr/bin/env python

import mapBehavior
import action
import motion
import unboard
import time
import logging
import qi

## \brief Behavior name
behaviorName = "carryBall"

# Macros
WALK_TIME = 3.0

# Global variables
firstPass = True
t0 = 0.0

## 	\brief Walk in open loop to carry ball to the goal
def behaviorAction():
    
    global firstPass
    global t0

    if(firstPass):
        t0 = time.time()
        firstPass = False
    
    # State led
    action.leds.SetRightEyeLeds(action.session, "cyan")
    
    action.movements.X = 0.9
    action.movements.Y = 0
    action.movements.Walk(action.session)
    
## 	\brief Transitions to walkBall_bot after some seconds
def behaviorTransition():
    
    global firstPass
    global t0

    t = time.time()

    if(t-t0 > WALK_TIME):
        firstPass = True
        logging.info("CARRY")
        return mapBehavior.walkBall_bot
    
    return mapBehavior.approachBall

