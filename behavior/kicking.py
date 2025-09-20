import mapBehavior
import action
import time
import logging

import unboard

# This is not a kicking behavior

def behaviorAction():
    if (unboard.seeBallTop == True):
        print(unboard.ballXTop,unboard.ballYTop)
        action.leds.SetLeftEyeLeds(action.session, "green")
    else:
        action.leds.SetLeftEyeLeds(action.session, "red")

    if (unboard.seeBallBot == True):
        print(unboard.ballXBot,unboard.ballYBot)
        action.leds.SetRightEyeLeds(action.session, "green")
    else:
        action.leds.SetRightEyeLeds(action.session, "red")




def behaviorTransition():
	return mapBehavior.kicking
		
