from Libs.Logs import logs
import time

class Communication:
    def __init__(self, session):
        self.session = session
        self.isRunning = True

    def run(self):
        logs.logger_communication.info("Running Communication")
        while self.isRunning:
            self.__process()
            time.sleep(0.001)

    def close(self):
        logs.logger_communication.info("Closing Communication")
        self.isRunning = False

    def __process(self):
        logs.logger_communication.info("code here")