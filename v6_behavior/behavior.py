#!/usr/bin/env python

import mapBehavior
import action
import unboard
import qi
import time
import logging


# Global variables
session = qi.Session()
gameState = 0
penalty = 0
buttonPressed = False
chestButtonState = False

## \brief Names de current state of the state machine, begins with initial behavior
current = mapBehavior.walkBall_bot


## 	\brief Main module of behavior thread
#   \details Calls action and transition of machine state and handles fall and game controller states
def main():

    global current
    global gameState
    global penalty
    global buttonPressed
    global chestButtonState

    # SETUP
    # Here we set up robot to play put robot in stand position and disable fallManager.

    memory_service = session.service("ALMemory")

    action.movements.enableFM = False
    action.movements.FallManager(action.session)

    action.movements.Position = "StandInit"
    action.movements.Stand(action.session)
    action.movements.StopWalk(action.session)


    while (True):

        # Check if robot isFalling
        action.movements.FallRecognition(action.session)
        if(action.movements.isFalling):
            # If robot has fallen it needs to stop walk before standing
            action.movements.X = float(0.0)
            action.movements.Y = float(0.0)
            action.movements.Theta = float(0.0)
            action.movements.Walk(action.session)
            action.movements.Position = "StandInit"
            action.movements.Stand(action.session)


        # Verify game state and penalties 
        gameState = int(unboard.gameState)
        penalty = int(unboard.penalty)

        gameState = 3

        # If chest button is touched
        # Possible values: ["ChestButtonPressed","ALChestButton/LongPressed","ALChestButton/DoubleClickOccurred","ALChestButton/SimpleClickOccurred"]
        if(memory_service.getData("ChestButtonPressed") and chestButtonState == False):
            if(buttonPressed == False):
                buttonPressed = True
            else:
                buttonPressed = False
            chestButtonState = True
        elif(not(memory_service.getData("ChestButtonPressed")) and chestButtonState == True):
            chestButtonState = False

        # Robot stays penalized if button is not pressed again
        if(buttonPressed == True):
            penalty = 1


        if(penalty):
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "red")

        elif(gameState == 0 ): # 0 = GAME_INITIAL
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "white")
        
        elif(gameState == 1 ): # 1 = GAME_READY
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "yellow")

        elif(gameState == 2 ): # 2 = GAME_SET
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "blue")

        elif(gameState == 3 ): # 3 = GAME_PLAYING
            action.leds.SetChestLeds(action.session, "green")
            mapBehavior.ballEyeLed.behaviorAction() 

            current.behaviorAction()
            current = current.behaviorTransition()

        elif(gameState == 4 ): # 4 = GAME_FINISHED
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "cyan")


