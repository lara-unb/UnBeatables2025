#include <action/speak/Speak.h>
#include <alcommon/alproxy.h>

#include "Logs/EasyLogging.h"
#include "ConnectionConfig.hpp"

Speak::Speak()
    : speakService(boost::make_shared<AL::ALProxy>(session, "ALTextToSpeech")) {

    LOG(INFO) << "\x1B[37m[SPEAK] Using the NAOqi SpeakService\x1B[0m";
    Speak::open();
}

Speak::~Speak() {
    Speak::close();
}

void Speak::open() {
    LOG(INFO) << "\x1B[37m[SPEAK] Opening NAOqi speakService\x1B[0m";
    try {
        speakService.setLanguage("Portuguese");
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to open speakService (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
    }
}

void Speak::close() {
    LOG(INFO) << "\x1B[37m[SPEAK] Closing NAOqi speakService\x1B[0m";
    try {
        speakService.exit();
    } catch (const std::exception& e) {
        LOG(ERROR) << "Failed to close speakService properly: " << e.what();
    }
}

void Speak::say(const std::string &text) {
    LOG(INFO) << "\x1B[37m[SPEAK] Saying: " << text << "\x1B[0m";
    speakService.say(text);
}
