#include <Logs/EasyLogging.h>
#include <thread>
#include "UnBeatables.hpp"
#include <ConnectionSettings.hpp>
#include <UnBoard.hpp>
#include <communication/teamController/TeamMessage.hpp>

// GLOBAL CONNECTION VARIABLES
NAOqiAddress naoqiAddress;
GameControllerAddress gameControllerAddress;
TeamCommunicationAddress teamCommunicationAddress;
qi::SessionPtr session;

// GLOBAL BLACKBOARD VARIABLES
PerceptionBoard perceptionBoard;
RoboCupGameControlData roboCupControlBoard;
UnBeatablesReturnBoard unbeatablesReturnBoard;

// GLOBAL STRATEGIES VARIABLES
SystemSettings systemSettings;

// GLOBAL TEAM MESSAGES VARIABLES
TeamMessage selfMessage;
TeamMessage teamMessages[MAX_ROBOTS];

UnBeatables::UnBeatables() {
    LOG(INFO) << "\x1B[32m[MAIN] Initializing UnBeatables\x1B[0m";
    initSession();
    builder = new Builder;
    communication = builder->buildCommunication();
    perception = builder->buildPerception();
    behavior = builder->buildBehavior();
}

void UnBeatables::close() const {
    if (communication) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing communication\x1B[0m";
        communication->close();
    }
    if (perception) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing perception\x1B[0m";
        perception->close();
    }
    if (behavior) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing behavior\x1B[0m";
        behavior->close();
    }
    if (session) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing session\x1B[0m";
        session->close();
    }
}

void UnBeatables::process() const{
    // std::thread t1([this] { perception->process(); });
    std::thread t2([this] { behavior->process(); });
    std::thread t3([this] { communication->process(); });

    // t1.join();
    t2.join();
    t3.join();
}

void UnBeatables::initSession() {
    session = qi::makeSession();
    LOG(INFO) << "\x1B[32m[MAIN] Connecting to " << naoqiAddress.ip << ":" << naoqiAddress.port;
    auto connectFuture = session->connect("tcp://" + naoqiAddress.ip + ":" + std::to_string(naoqiAddress.port));

    if (connectFuture.wait(3000) == qi::FutureState_Running)
        throw std::runtime_error("Connection timeout");
    if (connectFuture.hasError())
        throw std::runtime_error(connectFuture.error());

    LOG(INFO) << "\x1B[32m[MAIN] Successfully connected to NAOqi\x1B[0m";
}