# TODO: Look at making 1 single connection that does not reset every time that the loop goes through

import qi
from socket import *
from construct import Container, ConstError
from gamestate import GameState, RobotInfo, ReturnData, GAME_CONTROLLER_RESPONSE_VERSION
import logging
import unboard

session = qi.Session()

GAME_CONTROLLER_LISTEN_PORT = 3838
GAME_CONTROLLER_ANSWER_PORT = 3939


def main():
    udpSocket = socket(AF_INET, SOCK_DGRAM)
    try:
        udpSocket.bind(('192.168.0.255', GAME_CONTROLLER_LISTEN_PORT))
    except Exception as identifier:
        logging.exception("Bind error")
        if (identifier.errno == 98):  # addr already in use
            return
    try:
        while (1):
            data, peer = udpSocket.recvfrom(GameState.sizeof())

            logging.debug(len(data))

            parsed_state = GameState.parse(data)

            if(int(parsed_state.teams[0].team_number) == 1):
                unboard.teamNumber = 0
            else:
                unboard.teamNumber = 1

            # logging.debug("packet from broadcast is :" + peer[0])
            # for structKey, structValue in thisState.iteritems():
            #     logging.info("key: {} in struct recieved is {}".format(
            #         structKey, structValue))

            logging.debug("gamephase : {}".format(parsed_state.gamePhase))
            logging.debug("game_state : {}".format(parsed_state.game_state))
            logging.debug("first_half : {}".format(parsed_state.first_half))
            logging.debug("secsRemaining : {}".format(
                parsed_state.secsRemaining))
            logging.debug("penalty : {}".format(
                parsed_state.teams[unboard.teamNumber].players[unboard.playerNumber].penalty))

            # update unboard
            unboard.gameState = parsed_state.game_state
            # print("1", unboard.gameState)
            unboard.penalty = parsed_state.teams[unboard.teamNumber].players[unboard.playerNumber].penalty

            data = Container(
                header=b"RGrt",
                version = GAME_CONTROLLER_RESPONSE_VERSION,
                team = 1,  #UnBeatables number
                player = 4,
                message=0)

            try:
                destination = peer[0], GAME_CONTROLLER_ANSWER_PORT
                udpSocket.sendto(ReturnData.build(data), destination)
            except Exception as e:
                logger.exception("Network Error: %s" % str(e))
    finally:
        try:
            udpSocket.shutdown(SHUT_RDWR)
        except Exception as ex:
            logging.exception("could not shutdown")
        udpSocket.close()
