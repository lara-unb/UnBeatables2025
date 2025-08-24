#include <action/speak/Speak.h>
#include <alcommon/alproxy.h>

#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"

Speak::Speak()
    : speakService(boost::make_shared<AL::ALProxy>(session, "ALTextToSpeech")) {
    LOG(INFO) << "\x1B[37m[SPEAK] Using the NAOqi SpeakService\x1B[0m";
}

Speak::~Speak() {
    LOG(INFO) << "\x1B[37m[SPEAK] Stopping speakService\x1B[0m";
    speakService.exit();
}

void Speak::say(const std::string &text) {
    LOG(INFO) << "\x1B[37m[SPEAK] Saying: " << text << "\x1B[0m";
    speakService.say(text);
}
