#include <Logs/EasyLogging.h>

#include <thread>
#include "UnBeatables.hpp"
#include <ConnectionSettings.hpp>
#include <UnBoard.hpp>

// GLOBAL CONNECTION ATTRIBUTES
NAOqiAddress naoqiAddress;
GameControllerAddress gameControllerAddress;
qi::SessionPtr session;

// GLOBAL BLACKBOARD ATTRIBUTES
PerceptionBoard perceptionBoard;
RoboCupGameControlData roboCupControlBoard;
UnBeatablesReturnBoard unbeatablesReturnBoard;

// GLOBAL STRATEGIES ATTRIBUTES
SystemSettings systemSettings;

UnBeatables::UnBeatables() {
    LOG(INFO) << "\x1B[32m[MAIN] Initializing UnBeatables\x1B[0m";
    initSession();
    builder = new Builder;
    perception = builder->buildPerception();
    behavior = builder->buildBehavior();
    communication = builder->buildCommunication();
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