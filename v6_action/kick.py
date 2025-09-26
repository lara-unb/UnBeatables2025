# ESSE CHUTE FUNCIONA POREM MT LENTO E FRACO

#! /usr/bin/env python

import qi
import argparse
import sys
import motion
import time
import almath
import logging


def computePath(motion_service, effector, frame):
    dx1 = -0.02  # translation axis X (meters)
    dx2 = 0.05
    dy1 = -0.01
    dz1 = 0.01
    dz2 = 0.01  # translation axis Z (meters)
    dz3 = 0.01
    dwy = 1.0 * almath.TO_RAD  # rotation axis Y (radian)

    useSensorValues = False

    path = []
    currentTf = []
    try:
        currentTf = motion_service.getTransform(effector, frame,
                                                useSensorValues)
    except Exception, errorMsg:
        logging.exception(str(errorMsg))
        logging.exception("Error in kick")
        exit()

    targetTf = almath.Transform(currentTf)
    targetTf *= almath.Transform(dx1, dy1, dz1)
    targetTf *= almath.Transform().fromRotY(dwy)
    path.append(list(targetTf.toVector()))

    targetTf = almath.Transform(currentTf)
    targetTf *= almath.Transform(dx2, dy1, dz1)
    path.append(list(targetTf.toVector()))

    # targetTf = almath.Transform(currentTf)
    # targetTf *= almath.Transform(0.0, dy1, dz2)
    # path.append(list(targetTf.toVector()))

    targetTf = almath.Transform(currentTf)
    targetTf *= almath.Transform(0.0, dy1, dz3)
    path.append(list(targetTf.toVector()))

    path.append(currentTf)

    #path.append(currentTf)

    return path


def main(session):
    """
    Example of a whole body kick.
    Warning: Needs a PoseInit before executing
             Whole body balancer must be inactivated at the end of the script.
    This example is only compatible with NAO.
    """
    # Get the services ALMotion & ALRobotPosture.

    motion_service = session.service("ALMotion")
    posture_service = session.service("ALRobotPosture")

    # Wake up robot
    motion_service.wakeUp()

    # Send robot to Stand Init
    posture_service.goToPosture("StandInit", 0.5)

    # Activate Whole Body Balancer
    isEnabled = True
    motion_service.wbEnable(isEnabled)

    # Legs are constrained fixed
    stateName = "Fixed"
    supportLeg = "Legs"
    motion_service.wbFootState(stateName, supportLeg)

    # Constraint Balance Motion
    isEnable = True
    supportLeg = "Legs"
    motion_service.wbEnableBalanceConstraint(isEnable, supportLeg)

    # Support go to LLeg
    supportLeg = "LLeg"
    duration = 0.5
    motion_service.wbGoToBalance(supportLeg, duration)

    # RLeg is free
    stateName = "Free"
    supportLeg = "RLeg"
    motion_service.wbFootState(stateName, supportLeg)

    # RLeg is optimized
    effector = "RLeg"
    axisMask = 63
    frame = motion.FRAME_WORLD

    # Motion of the RLeg
    times = [0.5, 0.8, 1.5, 2.5]
    #times = [0.7, 1.0, 1.5, 3.0, 4.0]
    #times   = [2.0, 2.2, 3.0, 3.8, 5.0]

    path = computePath(motion_service, effector, frame)

    motion_service.transformInterpolations(effector, frame, path, axisMask,
                                           times)

    # Example showing how to Enable Effector Control as an Optimization
    isActive = False
    motion_service.wbEnableEffectorOptimization(effector, isActive)

    # Com go to LLeg
    # supportLeg = "RLeg"
    # duration   = 1.5
    # motion_service.wbGoToBalance(supportLeg, duration)

    # RLeg is free
    # stateName  = "Free"
    # supportLeg = "RLeg"
    # motion_service.wbFootState(stateName, supportLeg)

    # effector = "RLeg"
    # path = computePath(motion_service, effector, frame)
    # motion_service.transformInterpolations(effector, frame, path, axisMask, times)

    # time.sleep(1.0)

    # # Deactivate Head tracking
    # isEnabled = False
    # motion_service.wbEnable(isEnabled)

    # Legs are constrained fixed
    stateName = "Fixed"
    supportLeg = "Legs"
    motion_service.wbFootState(stateName, supportLeg)

    # Constraint Balance Motion
    isEnable = True
    supportLeg = "Legs"
    motion_service.wbEnableBalanceConstraint(isEnable, supportLeg)

    #send robot to Pose Init
    posture_service.goToPosture("StandInit", 0.3)

    # # Go to rest position
    # motion_service.rest()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--ip",
        type=str,
        default="127.0.0.1",
        help="Robot IP address. On robot or Local Naoqi: use '127.0.0.1'.")
    parser.add_argument("--port",
                        type=int,
                        default=9559,
                        help="Naoqi port number")

    args = parser.parse_args()
    session = qi.Session()
    try:
        session.connect("tcp://" + args.ip + ":" + str(args.port))
    except RuntimeError:
        logging.error(
            "Can't connect to Naoqi at ip \"" + args.ip + "\" on port " +
            str(args.port) + ".\n"
            "Please check your script arguments. Run with -h option for help.")
        sys.exit(1)
    main(session)
