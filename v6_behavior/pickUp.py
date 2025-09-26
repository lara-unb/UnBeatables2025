#!/usr/bin/env python

import mapBehavior
import action
import unboard

def behaviorAction():

    action.leds.SetEyeLeds(action.session, "red")
    action.movements.StopWalk(action.session)

def behaviorTransition():
    return mapBehavior.pickUp