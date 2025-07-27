#include <csignal>
#include <thread>

#include <EasyLogging.h>
#include <NaoqiLog.cpp>
#include "NaoConnectionConfig.hpp"
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
NaoConnectionConfig naoConfig;

std::shared_ptr<Perception> perception;

void signalHandler(int signum) {
    LOG(WARNING) << "\x1B[32m[MAIN] Process interrupted by signal " << signum << "\x1B[0m";
    if (perception) {
        LOG(INFO) << "\x1B[32m[MAIN] Closing perception\x1B[0m";
        perception->close();
    }
    exit(signum);
}

void configureLoggingSystem() {
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
    "\x1B[36m %datetime %level [%logger]\x1B[0m \t%msg");
    redirectNaoqiLogsToEasyLogging();
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
    LOG(INFO) << "\x1B[32m[MAIN] Connecting to NAO at " << naoConfig.ip << ":" << naoConfig.port << "\x1B[0m";

    try {
        configurePerception();
    }
    catch (const std::exception& ex) {
        LOG(ERROR) << "\x1B[31m[MAIN] Error while connecting or executing commands on NAO: " << ex.what() << "\x1B[0m";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}