#include <csignal>
#include <thread>

#include <Logs/EasyLogging.h>
#include <Logs/NaoqiLog.cpp>
#include <Config/INIParser.cpp>
#include "ConnectionConfig.hpp"
#include "perception/Perception.hpp"
#include "UnBoard.hpp"
#include "behavior/Behavior.hpp"
#include "communication/Communication.hpp"

INITIALIZE_EASYLOGGINGPP

PerceptionBoard perceptionBoard;
CommunicationBoard communicationBoard;


NAOqiAddress naoqiAddress;
GameControllerAddress gameControllerAddress;
qi::SessionPtr session;

std::shared_ptr<Perception> perception;
std::shared_ptr<Behavior> behavior;
std::shared_ptr<Communication> communication;

void close() {
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

void signalHandler(int signum) {
    LOG(WARNING) << "\x1B[32m[MAIN] Process interrupted by signal " << signum << "\x1B[0m";
    close();
    exit(signum);
}

void initLoggingSystem() {
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
    "\x1B[36m %datetime %level [%logger]\x1B[0m \t%msg");
    redirectNaoqiLogsToEasyLogging();
}

void initSession() {
    session = qi::makeSession();
    LOG(INFO) << "\x1B[32m[MAIN] Connecting to " << naoqiAddress.ip << ":" << naoqiAddress.port;
    auto connectFuture = session->connect("tcp://" + naoqiAddress.ip + ":" + std::to_string(naoqiAddress.port));

    if (connectFuture.wait(3000) == qi::FutureState_Running)
        throw std::runtime_error("Connection timeout");
    if (connectFuture.hasError())
        throw std::runtime_error(connectFuture.error());

    LOG(INFO) << "\x1B[32m[MAIN] Successfully connected to NAOqi\x1B[0m";
}

void initPerception() {
    perception = std::make_shared<Perception>();
    std::thread t(&Perception::process, perception);
    t.join();
}

void initBehavior() {
    behavior = std::make_shared<Behavior>();
    std::thread t(&Behavior::process, behavior);
    t.join();
}

void initCommunication() {
    communication = std::make_shared<Communication>();
    std::thread t(&Communication::process, communication);
    t.join();
}

int main() {
    std::signal(SIGINT, signalHandler);
    initLoggingSystem();
    loadConfig(naoqiAddress, gameControllerAddress);
    LOG(INFO) << "\x1B[32m[MAIN] Initializing Unboard\x1B[0m";

    try {
        // initSession();
        // initPerception();
        // initBehavior();
        initCommunication();
    }
    catch (const std::exception& ex) {
        LOG(ERROR) << "\x1B[31m[MAIN] Error while connecting or executing commands on NAO: " << ex.what() << "\x1B[0m";
        close();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}