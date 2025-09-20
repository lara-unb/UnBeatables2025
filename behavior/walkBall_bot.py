#!/usr/bin/env python

import mapBehavior
import action
import unboard
import logging
import os
import gameControllerExample

## \brief Behavior name
behaviorName = "walkBall_bot"


##  \brief Closed loop for walking ball when ball is seen in bot camera
def behaviorAction():
    mapBehavior.gameControllerExample    
    # State led
    action.leds.SetRightEyeLeds(action.session, "blue")

    # Adjust head
    action.movements.jointName = "HeadYaw"
    action.movements.Angle = 0.0
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    action.movements.jointName = "HeadPitch"
    action.movements.Angle = 29.0
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    # If ball is seen
    if(unboard.seeBallBot == True): 
        
        ballX = unboard.ballXBot
        ballY = unboard.ballYBot
        
        # print("BallX:", ballX)
        # print("BallYwalk:", ballY)

        # Walk ball in closed loop. 
        # Here we set the walk parametes according with ball position return in unboard.
        if(ballX < 0.4 and ballX > 0):
            action.movements.Y = float(2 * (0.5 - ballX))
            print("MOVIMENTO 1")
            if(action.movements.Y < 0.6):
                action.movements.Y = 0.6
                print("MOVIMENTO 1.1")
        elif(ballX > 0.6):
            action.movements.Y = float(2 * (0.5 - ballX))
            print("MOVIMENTO 2")
            if(action.movements.Y > -0.6):
                action.movements.Y = -0.6
                print("MOVIMENTO 2.2")
        else:
            action.movements.Y = float(0.0)

        if(ballY > 0.60 and ballY > 0):
            action.movements.X = float(1.8 * (0.6 - ballY))
            print("MOVIMENTO 3")
            if(action.movements.X < 0.8):
                action.movements.X = float(0.8)
                print("MOVIMENTO 3.3")

        action.movements.Theta = 0.0
        
        # else:
        #     action.movements.X = float(0.0)

        action.movements.Walk(action.session)

    # If ball is lost
    else:
        action.movements.StopWalk(action.session)

##  \brief  Transitions to walkBall_bot if ball is seen in bot camera. <br>
#           Transitions to walkBall_top if ball is seen in top camera. <br>
#           Transitions to carryBall if it has reached the ball. <br>
#           Transitions to lookForBall is ball is lost
def behaviorTransition():
    
    if(unboard.ballYBot > 0.6 and unboard.ballXBot > 0.5):
        logging.info("TesteKick")
        # testando chute
        action.movements.StopWalk(action.session)
        return mapBehavior.TesteKick
    
    elif(unboard.ballYBot > 0.6):
        logging.info("Carry")
        action.movements.StopWalk(action.session)
        return mapBehavior.carryBall

    elif(unboard.seeBallBot):
        #unboard.cntKick = 0
        return mapBehavior.walkBall_bot
        
    elif(unboard.seeBallTop):
        #unboard.cntKick = 0
        logging.info("walkBall_top")
        return mapBehavior.walkBall_top
    
    logging.info("lookForBall")
    #unboard.cntKick = 0
    return mapBehavior.lookForBall
    
