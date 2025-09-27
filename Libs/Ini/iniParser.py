import UnBoard

class ConfigLoader(object):
    def __init__(self, filename):
        self.filename = filename

    def apply(self):
        try:
            f = open(self.filename, "r")
        except IOError:
            raise RuntimeError("Fail to open {}".format(self.filename))

        for line in f:
            line = line.strip()
            if not line or line.startswith("#") or line.startswith("["):
                continue

            if '=' not in line:
                continue

            key, value = line.split('=', 1)
            key = key.strip()
            value = value.strip()

            if key == "NAOqiIP":
                UnBoard.naoqiAddress_ip = value
            elif key == "NAOqiPort":
                UnBoard.naoqiAddress_port = int(value)
            elif key == "gameControllerIP":
                UnBoard.gameControllerAddress_host = value
            elif key == "readingPort":
                UnBoard.gameControllerAddress_readingPort = int(value)
            elif key == "writingPort":
                UnBoard.gameControllerAddress_writingPort = int(value)
            elif key == "broadcast":
                UnBoard.teamCommunicationAddress_broadcast = value
            elif key == "multicast":
                UnBoard.teamCommunicationAddress_multicast = value
            elif key == "teamPort":
                UnBoard.teamCommunicationAddress_teamPort = int(value)
            elif key == "unbeatablesNumber":
                UnBoard.unbeatablesReturnBoard_teamNum = int(value)
            elif key == "playerNumber":
                UnBoard.unbeatablesReturnBoard_playerNum = int(value)
                UnBoard.selfMessage_playerNumber = int(value)
            elif key == "camera":
                UnBoard.systemSettings_camera = int(value)
            elif key == "cascade":
                UnBoard.systemSettings_cascade = value
        f.close()
