#include "Builder.hpp"
#include "UnBoard.hpp"
#include "ConnectionSettings.hpp"
#include "Logs/EasyLogging.h"
#include "perception/camera/NaoqiCamera.hpp"
#include "perception/camera/V4L2Camera.hpp"
#include "perception/detectors/BallDetector.hpp"
#include "communication/gameController/GameController.hpp"
#include "communication/teamController/TeamController.hpp"
#include "communication/socket/UDPClient.hpp"
#include "communication/socket/UDPServer.hpp"
#include "control/ControlsManager.hpp"
#include "control/controls/PS2Control.hpp"

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

    LOG(INFO) << "\x1B[32m[BUILDER] Communication - Using UDP Socket\x1B[0m";
    std::unique_ptr<UDPClient> gameControllerClient(new UDPClient(
        gameControllerAddress.host,
        gameControllerAddress.writingPort,
        SocketMode::UNICAST));

    std::unique_ptr<UDPServer> gameControllerServer(new UDPServer(
        gameControllerAddress.host,
        gameControllerAddress.readingPort,
        SocketMode::UNICAST));

    std::unique_ptr<UDPClient> teamClient(new UDPClient(
        teamCommunicationAddress.multicast,
        teamCommunicationAddress.teamPort,
        SocketMode::UNICAST));

    std::unique_ptr<UDPServer> teamServer(new UDPServer(
        teamCommunicationAddress.multicast,
        teamCommunicationAddress.teamPort,
        SocketMode::UNICAST));

    LOG(INFO) << "\x1B[32m[BUILDER] Communication - Using GameController\x1B[0m";
    std::unique_ptr<GameController> gameController(new GameController(gameControllerClient.release(), gameControllerServer.release()));

    LOG(INFO) << "\x1B[32m[BUILDER] Communication - Using TeamController\x1B[0m";
    std::unique_ptr<TeamController> teamController(new TeamController(teamClient.release(), teamServer.release()));

    return new Communication(gameController.release(), teamController.release());
}

ControlsManager* Builder::buildControlManager(){
    LOG(INFO) << "\x1B[32m[BUILDER] Control - Using PS2 controller\x1B[0m";
    std::unique_ptr<PS2Control> ps2Control(new PS2Control(controlState.device));
    return new ControlsManager(ps2Control.release());
}