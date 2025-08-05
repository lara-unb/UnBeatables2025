import mapBehavior
import action
import unboard
import qi
import time

session = qi.Session()

current = mapBehavior.walkBall_top
gameState = 3
penalty = 0
buttonPressed = False

#  \function for NAO says what we want
def speak(text):
    tts = session.service("ALTextToSpeech")
    tts.say(text) 


## \brief Main module of behavior thread
#   \details Calls action and transition of machine state and handles fall and game controller states
def main(is_simulation):

    global current
    global gameState
    global penalty
    global buttonPressed

    # SETUP
    # Here we set up robot to play, turn off autonomous mode, put robot in stand position.

    memory_service = session.service("ALMemory")

    if(not is_simulation):
        action.movements.enableFM = False
        action.movements.FallManager(action.session)

    try:
        life_service = session.service("ALAutonomousLife")
        if(life_service.getState() != "disabled"):
            life_service.setState("disabled")
    except:
        pass

    action.movements.Position = "StandInit"
    action.movements.Stand(action.session)

    while (True):

        if(not is_simulation):
            action.movements.FallRecognition(action.session)
            if(action.movements.isFalling):
                # action.movements.StiffnessControl(action.session, 0.0)
                time.sleep(1.0)
                action.movements.Position = "StandInit"
                action.movements.Stand(action.session)
                action.movements.WaitUntilMoveIsFinished(action.session)



        # Verify game state and penalties 
        # gameState = int(unboard.gameState)
        # penalty = int(unboard.penalty)

        if(not is_simulation):
            # If chest button is touched
            # Possible values: ["ChestButtonPressed","ALChestButton/LongPressed","ALChestButton/DoubleClickOccurred","ALChestButton/SimpleClickOccurred"]
            # chestButtonState = memory_service.getData("ChestButtonPressed")
            # if (chestButtonState):
            #     if(buttonPressed == False):
            #         buttonPressed = True
            #     else:
            #         buttonPressed = False

            # Robot stays penalized if button is not pressed again
            if(buttonPressed == True):
                penalty = 1

        gameState = 3


        if(gameState == 3): # 3 = GAME_PLAYING
            if(penalty != 0):
                mapBehavior.pickUp.behaviorAction()
                action.leds.SetChestLeds(action.session, "red")
            else:
                action.leds.SetChestLeds(action.session, "green")
                mapBehavior.ballEyeLed.behaviorAction() 

                current.behaviorAction()
                current = current.behaviorTransition()

        elif(gameState == 0 ): # 0 = GAME_INITIAL
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "white")
        
        elif(gameState == 1 ): # 1 = GAME_READY
            mapBehavior.pickUp.behaviorAction()
... (9 lines left)
Collapse
message.txt
4 KB
﻿
#!/usr/bin/env python

import mapBehavior
import action
import unboard
import qi
import time

session = qi.Session()

current = mapBehavior.walkBall_top
gameState = 3
penalty = 0
buttonPressed = False

#  \function for NAO says what we want
def speak(text):
    tts = session.service("ALTextToSpeech")
    tts.say(text) 


## 	\brief Main module of behavior thread
#   \details Calls action and transition of machine state and handles fall and game controller states
def main(is_simulation):

    global current
    global gameState
    global penalty
    global buttonPressed

    # SETUP
    # Here we set up robot to play, turn off autonomous mode, put robot in stand position.

    memory_service = session.service("ALMemory")

    if(not is_simulation):
        action.movements.enableFM = False
        action.movements.FallManager(action.session)

    try:
        life_service = session.service("ALAutonomousLife")
        if(life_service.getState() != "disabled"):
            life_service.setState("disabled")
    except:
        pass

    action.movements.Position = "StandInit"
    action.movements.Stand(action.session)

    while (True):

        if(not is_simulation):
            action.movements.FallRecognition(action.session)
            if(action.movements.isFalling):
                # action.movements.StiffnessControl(action.session, 0.0)
                time.sleep(1.0)
                action.movements.Position = "StandInit"
                action.movements.Stand(action.session)
                action.movements.WaitUntilMoveIsFinished(action.session)



        # Verify game state and penalties 
        # gameState = int(unboard.gameState)
        # penalty = int(unboard.penalty)

        if(not is_simulation):
            # If chest button is touched
            # Possible values: ["ChestButtonPressed","ALChestButton/LongPressed","ALChestButton/DoubleClickOccurred","ALChestButton/SimpleClickOccurred"]
            # chestButtonState = memory_service.getData("ChestButtonPressed")
            # if (chestButtonState):
            #     if(buttonPressed == False):
            #         buttonPressed = True
            #     else:
            #         buttonPressed = False

            # Robot stays penalized if button is not pressed again
            if(buttonPressed == True):
                penalty = 1

        gameState = 3


        if(gameState == 3): # 3 = GAME_PLAYING
            if(penalty != 0):
                mapBehavior.pickUp.behaviorAction()
                action.leds.SetChestLeds(action.session, "red")
            else:
                action.leds.SetChestLeds(action.session, "green")
                mapBehavior.ballEyeLed.behaviorAction() 

                current.behaviorAction()
                current = current.behaviorTransition()

        elif(gameState == 0 ): # 0 = GAME_INITIAL
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "white")
        
        elif(gameState == 1 ): # 1 = GAME_READY
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "yellow")

        elif(gameState == 2 ): # 2 = GAME_SET
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "blue")

        elif(gameState == 4 ): # 1 = GAME_FINISHED
            mapBehavior.pickUp.behaviorAction()
            action.leds.SetChestLeds(action.session, "cyan")

