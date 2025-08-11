#include <csignal>
#include <thread>

#include <Logs/EasyLogging.h>
#include <Logs/NaoqiLog.cpp>
#include "ConnectionConfig.hpp"
#include "perception/Perception.hpp"
#include "UnBoard.hpp"

INITIALIZE_EASYLOGGINGPP

std::string logo = R"(
  _    _       ____             _        _     _
 | |  | |     |  _ \           | |      | |   | |
 | |  | |_ __ | |_) | ___  __ _| |_ __ _| |__ | | ___  ___
 | |  | | '_ \|  _ < / _ \/ _` | __/ _` | '_ \| |/ _ \/ __|
 | |__| | | | | |_) |  __/ (_| | || (_| | |_) | |  __/\__ \
  \____/|_| |_|____/ \___|\__,_|\__\__,_|_.__/|_|\___||___/

)";

PerceptionBoard perceptionBoard;
CommunicationBoard communicationBoard;
ConnectionConfig connectionConfig;
qi::SessionPtr session;

std::shared_ptr<Perception> perception;

void signalHandler(int signum) {
    LOG(WARNING) << "\x1B[32m[MAIN] Process interrupted by signal " << signum << "\x1B[0m";
    if (perception) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing perception\x1B[0m";
        perception->close();
    }
    if (session) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing session\x1B[0m";
        session->close();
    }
    exit(signum);
}

void configureLoggingSystem() {
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
    "\x1B[36m %datetime %level [%logger]\x1B[0m \t%msg");
    redirectNaoqiLogsToEasyLogging();
}

void configureSession() {
    session = qi::makeSession();
    LOG(INFO) << "\x1B[32m[MAIN] Connecting to " << connectionConfig.ip << ":" << connectionConfig.port;
    auto connectFuture = session->connect("tcp://" + connectionConfig.ip + ":" + std::to_string(connectionConfig.port));

    if (connectFuture.wait(3000) == qi::FutureState_Running)
        throw std::runtime_error("Connection timeout");
    if (connectFuture.hasError())
        throw std::runtime_error(connectFuture.error());

    LOG(INFO) << "\x1B[32m[MAIN] Successfully connected to NAOqi\x1B[0m";
}

void configurePerception() {
    perception = std::make_shared<Perception>();
    std::thread t(&Perception::process, perception);
    t.join();
}

int main() {
    std::signal(SIGINT, signalHandler);

    configureLoggingSystem();

    LOG(INFO) << "\x1B[32m" << logo << "\x1B[0m";
    LOG(INFO) << "\x1B[32m[MAIN] Initializing Unboard\x1B[0m";

    try {
        configureSession();
        configurePerception();
    }
    catch (const std::exception& ex) {
        LOG(ERROR) << "\x1B[31m[MAIN] Error while connecting or executing commands on NAO: " << ex.what() << "\x1B[0m";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}