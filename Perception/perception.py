from Libs.Logs import logs
import time

class Perception:
    def __init__(self, session):
        self.session = session
        self.isRunning = True

    def run(self):
        logs.logger_perception.info("Running Perception")
        while self.isRunning:
            self.__process()
            time.sleep(0.001)

    def close(self):
        logs.logger_perception.info("Closing Perception")
        self.isRunning = False

    def __process(self):
        logs.logger_perception.info("code here")