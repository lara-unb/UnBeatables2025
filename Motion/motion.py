from Libs.Logs import logs
import time

class Motion:
    def __init__(self, session):
        self.session = session
        self.isRunning = True

    def run(self):
        logs.logger_motion.info("Running Motion")
        while self.isRunning:
            self.__process()
            time.sleep(0.001)

    def close(self):
        logs.logger_motion.info("Closing Motion")
        self.isRunning = False

    def __process(self):
        logs.logger_motion.info("code here")