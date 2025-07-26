#include <alcommon/albroker.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <iostream>

#include <EasyLogging.h>
#include <NaoqiLog.cpp>

INITIALIZE_EASYLOGGINGPP

std::string logo = R"(
  _    _       ____             _        _     _
 | |  | |     |  _ \           | |      | |   | |
 | |  | |_ __ | |_) | ___  __ _| |_ __ _| |__ | | ___  ___
 | |  | | '_ \|  _ < / _ \/ _` | __/ _` | '_ \| |/ _ \/ __|
 | |__| | | | | |_) |  __/ (_| | || (_| | |_) | |  __/\__ \
  \____/|_| |_|____/ \___|\__,_|\__\__,_|_.__/|_|\___||___/

)";

struct NaoConnectionConfig {
    std::string ip = "127.0.0.2";
    int port = 9559;
};
NaoConnectionConfig naoConfig;

void configureLoggingSystem() {
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
    "\x1B[36m %datetime %level [%logger]\x1B[0m %msg");
    redirectNaoqiLogsToEasyLogging();
}

int main() {
    configureLoggingSystem();
    LOG(INFO) << "\x1B[32m" << logo << "\x1B[0m";
    LOG(INFO) << "\x1B[32m[MAIN] Connecting to NAO at " << naoConfig.ip << ":" << naoConfig.port << "\x1B[0m";

    try {
        auto naoBroker = AL::ALBroker::createBroker(
            "NaoBroker",
            "",
            0,
            naoConfig.ip,
            naoConfig.port
        );

        AL::ALTextToSpeechProxy ttsProxy(naoConfig.ip, naoConfig.port);
        AL::ALMotionProxy motionProxy(naoConfig.ip, naoConfig.port);

        motionProxy.wakeUp();

        ttsProxy.say("Hello, UnBeatables!");

        motionProxy.rest();

    }
    catch (const std::exception& ex) {
        LOG(ERROR) << "\x1B[31mError while connecting or executing commands on NAO: " << ex.what() << "\x1B[0m";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}