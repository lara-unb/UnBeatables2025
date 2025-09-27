import logging
import sys
import time

RESET = "\033[0m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
GREEN = "\033[32m"
GRAY = "\033[37m"
PURPLE = "\033[35m"
ORANGE = "\033[38;5;208m"

COLUMN_WIDTH = 35

class ColorFormatter(logging.Formatter):
    def __init__(self, color):
        logging.Formatter.__init__(self)
        self.color = color

    def format(self, record):
        ts = time.strftime("%H:%M:%S", time.localtime()) + ":%03d" % int((time.time() % 1)*1000)
        prefix = "{} - [{}]:".format(record.name, ts)
        prefix_aligned = prefix.ljust(COLUMN_WIDTH)
        msg = "{} {}".format(prefix_aligned, record.getMessage())
        return self.color + msg + RESET

def get_logger(name, color, level=logging.INFO):
    logger = logging.getLogger(name)
    logger.setLevel(level)
    logger.propagate = False

    if not logger.handlers:
        ch = logging.StreamHandler(sys.stdout)
        ch.setFormatter(ColorFormatter(color))
        logger.addHandler(ch)

    return logger

logger_perception = get_logger("Perception", YELLOW)
logger_communication = get_logger("Communication", BLUE)
logger_behavior = get_logger("Behavior", GREEN)
logger_motion = get_logger("Motion", ORANGE)
logger_main = get_logger("Main", PURPLE)

if __name__ == "__main__":
    logger_main.info("Starting main program")
    logger_perception.info("Perception module started")
    logger_communication.info("Communication module started")
    logger_behavior.info("Behavior module started")
    logger_motion.info("Motion module started")

    logger_perception.warning("Perception warning")
    logger_communication.error("Communication error")
