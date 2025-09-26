import qi
import action 
import logging
import mapBehavior
import unboard

behaviorName = "TesteKick"

def behaviorAction():
    
    motion = action.session.service("ALMotion")
    
   action.leds.SetRightEyeLeds(action.session 
,"green")
    
    if(unboard.ballYBot > 0.6 and unboard.ballXBot > 0.5):   
    	name = unboard.names
    	timee = unboard.times
    	key = unboard.keys
 
        motion.angleInterpolationBezier(name, timee, key)
    	print("CHUTEI")

def behaviorTransition():
        
    
    action.movements.StopWalk(action.session)
    unboard.ballYBot = 0
    unboard.ballXbot = 0
     
    return mapBehavior.walkBall_bot
