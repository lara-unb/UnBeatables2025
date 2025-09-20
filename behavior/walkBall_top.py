#!/usr/bin/env python

import mapBehavior
import action
import unboard
import logging

##  \brief Behavior name
behaviorName = "walkBall_top"

# Global variables
lastBallY = 0.0

## 	\brief Closed loop for walking ball when ball is seen in top camera
def behaviorAction():
    global lastBallY

    # State led
    action.leds.SetRightEyeLeds(action.session, "white")

    # Adjust head
    action.movements.jointName = "HeadYaw"
    action.movements.Angle = 0.0
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    action.movements.jointName = "HeadPitch"
    action.movements.Angle = 20.0
    action.movements.MaxSpeed = 0.1
    action.movements.HeadMove(action.session)

    if(unboard.seeBallTop == True): 

        # print("ESTOU NO WALK_TOP")
        ballX = unboard.ballXTop
        ballY = unboard.ballYTop
        # print("BallX:", ballX)
        # print("BallY:", ballY)

        # Walk ball in closed loop. 
        # Here we set the walk parametes according with ball position return in unboard.
        if(ballX < 0.4 and ballX != -1):
            action.movements.Y = float(2 * (0.5 - ballX))
        elif(ballX > 0.7 and ballX != -1):
            action.movements.Y = float(2 * (0.5 - ballX))
        else:
            action.movements.Y = float(0.0)

        if(ballY < 0.80 and ballY != -1):
            action.movements.X = float(0.8)
        # else:
        #     action.movements.X = float(0.0)

        action.movements.Theta = 0.0
        
        action.movements.Walk(action.session)

        lastBallY = ballY

    # else:
    #     action.movements.StopWalk(action.session)



## 	\brief  Transitions to walkBall_bot if ball is seen in bot camera. <br>
#           Transitions to approachBall if ballY is too low on top camera. <br>
#           Transitions to walkBall_top if ball is seen in top camera. <br>
#           Transitions to lookForBall if ball is lost.
def behaviorTransition():   
    global lastBallY

    if(unboard.seeBallBot):
        lastBallY = 0
        logging.info("walkBall_bot")
        return mapBehavior.walkBall_bot

    elif(lastBallY > 0.8):
        lastBallY = 0
        logging.info("approachBall")
        return mapBehavior.approachBall

    elif(unboard.seeBallTop):
        return mapBehavior.walkBall_top

    else:
        lastBallY = 0
        logging.info("lookForBall")
        return mapBehavior.lookForBall
        