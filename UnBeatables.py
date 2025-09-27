import signal
import sys
import threading
import logging
import qi

import UnBoard
from Libs.Ini.iniParser import ConfigLoader
from Libs.Logs import logs

from Behavior.behavior import Behavior
from Communication.communication import Communication
from Motion.motion import Motion
from Perception.perception import Perception

logging.basicConfig(level=logging.INFO)

class UnBeatables:
    def __init__(self, ip="127.0.0.1", port=9559):
        self.ip = ip
        self.port = port
        self.session = qi.Session()
        try:
            self.session.connect("tcp://{0}:{1}".format(self.ip, self.port))
            logs.logger_main.info("Connected to NAOqi at {0}:{1}".format(self.ip, self.port))
        except RuntimeError:
            logs.logger_main.exception("Could not connect to NAOqi at {0}:{1}".format(self.ip, self.port))
            sys.exit(1)

        self.motion = Motion(self.session)
        self.behavior = Behavior(self.session)
        self.perception = Perception(self.session)
        self.communication = Communication(self.session)

        self.behavior_thread = None
        self.perception_thread = None
        self.communication_thread = None

    def start_threads(self):
        logs.logger_main.info("Starting threads...")
        self.behavior_thread = threading.Thread(target=self.behavior.run)
        self.perception_thread = threading.Thread(target=self.perception.run)
        self.communication_thread = threading.Thread(target=self.communication.run)

        self.behavior_thread.start()
        self.perception_thread.start()
        self.communication_thread.start()

    def join_threads(self):
        if self.behavior_thread:
            self.behavior_thread.join()
        if self.perception_thread:
            self.perception_thread.join()
        if self.communication_thread:
            self.communication_thread.join()

    def shutdown(self, *_):
        logs.logger_main.info("Ctrl+C detected, shutting down modules...")
        try: self.behavior.close()
        except Exception as e: logs.logger_main.error("Error closing Behavior: {0}".format(e))
        try: self.perception.close()
        except Exception as e: logs.logger_main.error("Error closing Perception: {0}".format(e))
        try: self.motion.close()
        except Exception as e: logs.logger_main.error("Error closing Motion: {0}".format(e))
        try: self.communication.close()
        except Exception as e: logs.logger_main.error("Error closing Communication: {0}".format(e))
        logs.logger_main.info("All modules closed. Exiting program.")
        sys.exit(0)


if __name__ == "__main__":
    loader = ConfigLoader("config.ini")
    loader.apply()

    nao = UnBeatables(ip=UnBoard.naoqiAddress_ip,
                      port=UnBoard.naoqiAddress_port)
    signal.signal(signal.SIGINT, nao.shutdown)
    nao.start_threads()
    signal.pause()
