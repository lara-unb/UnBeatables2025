#!/usr/bin/env python

import mapBehavior
import action
import unboard

def behaviorAction():

    if(unboard.seeBallBot == True): 
            action.leds.SetLeftEyeLeds(action.session, "green")
    elif(unboard.seeBallTop == True): 
            action.leds.SetLeftEyeLeds(action.session, "blue")
    else: 
            action.leds.SetLeftEyeLeds(action.session, "red")