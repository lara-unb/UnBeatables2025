#include <UnBeatables.hpp>
#include <csignal>
#include <Logs/EasyLogging.h>
#include <Logs/NaoqiLog.cpp>
#include <Config/INIParser.cpp>

INITIALIZE_EASYLOGGINGPP

UnBeatables *unbeatables;

void signalHandler(int signum) {
    LOG(WARNING) << "\x1B[32m[MAIN] Process interrupted by signal " << signum << "\x1B[0m";
    unbeatables->close();
    exit(signum);
}

void initLoggingSystem() {
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
    "\x1B[36m %datetime %level [%logger]\x1B[0m \t%msg");
    redirectNaoqiLogsToEasyLogging();
}

int main() {
    std::signal(SIGINT, signalHandler);
    initLoggingSystem();
    loadConfig();
    LOG(INFO) << "\x1B[32m[MAIN] Initializing Unboard\x1B[0m";
    try {
        unbeatables = new UnBeatables();
        unbeatables->process();
    }
    catch (const std::exception& ex) {
        LOG(ERROR) << "\x1B[31m[MAIN] Error while connecting or executing commands on NAO: " << ex.what() << "\x1B[0m";
        unbeatables->close();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}