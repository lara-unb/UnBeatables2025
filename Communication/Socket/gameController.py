import socket
import struct
import threading
from Queue import Queue


class GameController:
    def __init__(self, ):

        self.GAMECONTROLLER_DATA_PORT = 3838
        self.GAMECONTROLLER_RETURN_PORT = 3939
        self.MAX_NUM_PLAYERS = 20

        self.packet_queue = Queue()

    def parseGameControlData(self, data):

        try:
            header = data[:4]
            if header != "RGme":
                print("Unexpected header for game control data: "), header
                return
            decoded = self.decode(data)
            self.packet_queue.put(decoded)
        except Exception as e:
            print("Failed to parse Game Control Data: "), e

    # ToDo
    def parseGameControlReturnData(data):
        try:
            pass
        except Exception as e:
            print("Failed to parse Game Control Return Data: "), e

    def listenOnPort(self, port, handler):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('', port))
        print("Listening on port "), port, "..."

        while True:
            data, addr = sock.recvfrom(1024)
            handler(data)

    def startListeners(self):
        threads = []
        ports = {
            self.GAMECONTROLLER_DATA_PORT: self.parseGameControlData,
            self.GAMECONTROLLER_RETURN_PORT: self.parseGameControlReturnData,
        }

        for port, handler in ports.items():
            thread = threading.Thread(target=self.listenOnPort, args=(port, handler))
            thread.daemon = True
            thread.start()
            threads.append(thread)

        for thread in threads:
            thread.join()

    def decode(self, data):
        header, version, packetNumber, playersPerTeam, competitionPhase, competitionType, gamePhase, state, setPlay, firstHalf, kickingTeam, secsRemaining, secondaryTime = struct.unpack_from(
            '4s10B2h', data)
        offset = struct.calcsize('4s10B2h')
        team01 = self.decodeTeam(data, offset)
        offset = team01[1]
        team02 = self.decodeTeam(data, offset)
        return {
            'header': header,
            'version': version,
            'packetNumber': packetNumber,
            'playersPerTeam': playersPerTeam,
            'competitionPhase': competitionPhase,
            'competitionType': competitionType,
            'gamePhase': gamePhase,
            'state': state,
            'setPlay': setPlay,
            'firstHalf': firstHalf,
            'kickingTeam': kickingTeam,
            'secsRemaining': secsRemaining,
            'secondaryTime': secondaryTime,
            'TeamInfo': [team01[0], team02[0]]
        }

    def decodeTeam(self, data, offset):
        teamNumber, fieldPlayerColour, goalkeeperColour, goalkeeper, score, penaltyShot, singleShots, messageBudget = struct.unpack_from(
            '6B2H', data, offset)
        offset += struct.calcsize('6B2H')
        robot = self.decodeRobot(data, offset)

        return [{'teamNumber': teamNumber,
                 'fieldPlayerColour': fieldPlayerColour,
                 'goalkeeperColour': goalkeeperColour,
                 'goalkeeper': goalkeeper,
                 'score': score,
                 'penaltyShot': penaltyShot,
                 'singleShots': singleShots,
                 'messageBudget': messageBudget,
                 'RobotInfo': robot[0]
                 }, robot[1]]

    def decodeRobot(self, data, offset):
        robotInfo = []
        for c in range(0, self.MAX_NUM_PLAYERS):
            penalty, secsTillUnpenalised = struct.unpack_from('2B', data, offset)
            offset += struct.calcsize('2B')
            robotInfo.append({'penalty': penalty,
                              'secsTillUnpenalised': secsTillUnpenalised
                              })
        return [robotInfo, offset]
