#!/usr/bin/env python

import mapBehavior
import action
import unboard
import logging

## \brief Behavior name
behaviorName = "faceBall_bot"
firstPass = True


def behaviorAction():

    action.movements.Position = "StandInit"
    # action.movements.Stand(action.session)

    # State led
    action.leds.SetRightEyeLeds(action.session, "magenta")

    # Adjust head
    action.movements.jointName = "HeadYaw"
    action.movements.Angle = 60
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    action.movements.jointName = "HeadPitch"
    action.movements.Angle = 10
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)


    action.movements.WaitUntilMoveIsFinished(action.session)


    action.movements.jointName = "HeadYaw"
    action.movements.Angle = -60
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    action.movements.jointName = "HeadPitch"
    action.movements.Angle = 10
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    action.movements.WaitUntilMoveIsFinished(action.session)

    print(2)



def behaviorTransition():   
    return mapBehavior.faceBall_bot


