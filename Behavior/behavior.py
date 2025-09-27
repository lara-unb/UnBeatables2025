from Libs.Logs import logs
import time

class Behavior:
    def __init__(self, session):
        self.session = session
        self.isRunning = True

    def run(self):
        logs.logger_behavior.info("Running Behavior")
        while self.isRunning:
            self.__process()
            time.sleep(0.001)

    def close(self):
        logs.logger_behavior.info("Closing Behavior")
        self.isRunning = False

    def __process(self):
        logs.logger_behavior.info("code here")