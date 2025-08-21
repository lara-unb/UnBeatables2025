#include "Builder.hpp"
#include "UnBoard.hpp"
#include "ConnectionSettings.hpp"
#include "Logs/EasyLogging.h"
#include "perception/camera/NaoqiCamera.hpp"
#include "perception/camera/V4L2Camera.hpp"
#include "perception/detectors/BallDetector.hpp"
#include "communication/gameController/GameController.hpp"
#include "communication/socket/client/TCPClient.hpp"
#include "communication/socket/client/UDPClient.hpp"
#include "communication/socket/server/TCPServer.hpp"
#include "communication/socket/server/UDPServer.hpp"

Behavior* Builder::buildBehavior() {
    return new Behavior();
}

Perception* Builder::buildPerception() {
    LOG(INFO) << "\x1B[32m[BUILDER] Perception - Using cascade (" << systemSettings.cascade <<")\x1B[0m";
    std::unique_ptr<BallDetector> ballDetector(new BallDetector(systemSettings.cascade));

    std::unique_ptr<Camera> camera;
    switch (systemSettings.camera) {
        case NAOQI_CAMERA:
            LOG(INFO) << "\x1B[32m[BUILDER] Perception - Using NAOqiCamera\x1B[0m";
            camera.reset(new NaoqiCamera());
            break;
        case V4L2_CAMERA:
            LOG(INFO) << "\x1B[32m[BUILDER] Perception - Using V4L2Camera\x1B[0m";
            camera.reset(new V4L2Camera());
            break;
        default:
            throw std::runtime_error("Camera strategy not found");
    }

    return new Perception(camera.release(), ballDetector.release());
}


Communication* Builder::buildCommunication(){
    LOG(INFO) << "\x1B[32m[BUILDER] Communication - Using GameController\x1B[0m";
    std::unique_ptr<GameController> gameController(new GameController());

    std::unique_ptr<Client> gameControllerClient;
    std::unique_ptr<Server> gameControllerServer;
    std::unique_ptr<Client> teamClient;
    std::unique_ptr<Server> teamServer;
    switch (systemSettings.network) {
        case UDP_NETWORK:
            LOG(INFO) << "\x1B[32m[BUILDER] Communication - Using UDP Socket\x1B[0m";
            gameControllerClient.reset(new UDPClient(
                gameControllerAddress.host,
                gameControllerAddress.writingPort,
                SocketMode::UNICAST));

            gameControllerServer.reset(new UDPServer(
                gameControllerAddress.host,
                gameControllerAddress.readingPort,
                SocketMode::UNICAST));

            teamClient.reset(new UDPClient(
                gameControllerAddress.host,
                teamCommunicationAddress.teamPort,
                SocketMode::BROADCAST));

            teamServer.reset(new UDPServer(
                teamCommunicationAddress.multicast,
                teamCommunicationAddress.teamPort,
                SocketMode::BROADCAST));
            break;

        case TCP_NETWORK:
            LOG(INFO) << "\x1B[32m[BUILDER] Communication - Using TCP Socket\x1B[0m";
            gameControllerClient.reset(new TCPClient(
                gameControllerAddress.host,
                gameControllerAddress.writingPort,
                SocketMode::UNICAST));

            gameControllerServer.reset(new TCPServer(
                gameControllerAddress.host,
                gameControllerAddress.readingPort,
                SocketMode::UNICAST));

            teamClient.reset(new TCPClient(
                gameControllerAddress.host,
                teamCommunicationAddress.teamPort,
                SocketMode::BROADCAST));

            teamServer.reset(new TCPServer(
                teamCommunicationAddress.multicast,
                teamCommunicationAddress.teamPort,
                SocketMode::BROADCAST));
            break;
        default:
            throw std::runtime_error("Network strategy not found");
    }
    return new Communication(gameController.release(), gameControllerClient.release(), gameControllerServer.release());
}