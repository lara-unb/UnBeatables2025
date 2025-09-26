# Behavior

The behavior manages the state machine responsible for making the robot play. It handles the strategies of the time.

## Structure

* __behavior.py__

This module will be called with its own thread in the unbeatables.py module. It calls the functions behaviorAction and behaviorTransition in a loop.

* __mapBehavior.py__

This module lists all the behaviors implemented and must be imported in all these behaviors.

### Behavior modules

* approachBall
* ballEyeLed
* carryBall
* lookForBall
* walkBall_bot
* walkBall_top
