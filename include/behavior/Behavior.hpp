miti
miti9004
Invisible

Withy
 started a call that lasted 3 hours. — 7/22/2025 9:32 PM
Withy — 7/22/2025 9:35 PM
2MGROUPMEMBERS 
Withy
 started a call that lasted 4 hours. — 7/27/2025 1:39 PM
carol
 started a call that lasted 5 hours. — 7/27/2025 7:34 PM
carol — 7/27/2025 8:33 PM
molier, me avisa no zap quando vc terminar de comer heheheh
Withy — 7/27/2025 8:33 PM
Me respinder no zap ngm quer
Safadas
carol — 7/27/2025 8:41 PM
oxi, eu respondi
Withy — 7/27/2025 10:47 PM
Image
Image
Withy — 7/27/2025 11:36 PM
Image
carol
 started a call that lasted 2 hours. — 7/29/2025 8:30 PM
miti — 7/29/2025 8:32 PM
@amormor
me ame dnv
volte
TT
carol — 7/29/2025 8:33 PM
no, fique longe e deixe ela para mim
hehehehhe
miti — 7/29/2025 8:33 PM
slk
compensa na vdd
carol — 7/29/2025 8:33 PM
fiquei tímida...
Withy — 7/29/2025 11:40 PM
@carol
vai no carrinho
lá fora
tem 26 k
esse n
na porta
You missed a call from 
Withy
 that lasted 8 minutes. — 8/1/2025 8:47 PM
miti
 started a call that lasted 13 minutes. — 8/1/2025 9:26 PM
carol — 8/1/2025 9:33 PM
oioiiii
vem server
miti — 8/1/2025 10:20 PM
molier
vai mais uma?
@carol
miti
 started a call that lasted 2 hours. — 8/2/2025 9:37 PM
miti — 8/2/2025 10:01 PM
https://youtube.com/shorts/XeyAXo8BLb4?si=uzjHZDuz2qK4pYRz
YouTube
BARDINETTE
How to tilt a Darius player
Image
Withy — 8/2/2025 10:03 PM
https://www.youtube.com/shorts/Y2NZ-R8TyHg
YouTube
PhiZe
video original funk do coreano
Image
appetrexo
 started a call that lasted 3 hours. — 8/3/2025 8:49 PM
carol — 8/3/2025 9:32 PM
amor
appetrexo — 8/3/2025 9:32 PM
eueu
carol — 8/3/2025 9:32 PM
qual é o negócio para quando da tela preta?
appetrexo — 8/3/2025 9:33 PM
ctrl + windows + shift + b
só funciona quando o caps lock tá dando cor 
carol — 8/3/2025 9:33 PM
mé
bou reiniciar
carol — 8/3/2025 9:47 PM
1 seg amor
appetrexo — 8/3/2025 9:47 PM
fechou, momo
te amo
miti
 started a call that lasted 2 hours. — Yesterday at 11:13 PM
appetrexo — 12:22 AM
Image
miti
 started a call. — 11:34 AM
carol — 12:14 PM
debsfranca
lukiranha#A1
Withy — 3:51 PM
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

