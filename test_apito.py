import qi
import argparse
import sys
import time


def main(session):
    """
    This example uses the setParameter method.
    """
    # Get the service ALSoundDetection.

    memory_service = session.service("ALMemory")

    sound_service = session.service("ALAudioDevice")
    # sound_detect_service.subscribe("ALSoundDetection")

    # Sets the sensitivity of the detection to 0.3 (less sensitive than default).
    # The default value is 0.9.
    # sound_detect_service.setParameter("Sensitivity", 0.5)
    # print "Sensitivity set to 0.3"

    while(1):
        time.sleep(0.3)
        print(sound_service.getLeftMicEnergy(),sound_service.getRightMicEnergy(), sound_service.getFrontMicEnergy(), sound_service.getRearMicEnergy())
        





if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip", type=str, default="127.0.0.1",
                        help="Robot IP address. On robot or Local Naoqi: use '127.0.0.1'.")
    parser.add_argument("--port", type=int, default=9559,
                        help="Naoqi port number")

    args = parser.parse_args()
    session = qi.Session()
    try:
        session.connect("tcp://" + args.ip + ":" + str(args.port))
    except RuntimeError:
        print ("Can't connect to Naoqi at ip \"" + args.ip + "\" on port " + str(args.port) +".\n"
               "Please check your script arguments. Run with -h option for help.")
        sys.exit(1)
    main(session)