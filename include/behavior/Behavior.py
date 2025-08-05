#pragma once
#include <qi/session.hpp>
#include <alproxies/altexttospeechproxy.h>
#include <iostream>

class Behavior {
void speak(boost::shared_ptr<qi::Session> session, const std::string& text) {
    try {
        AL::ALTextToSpeechProxy tts(session, "ALTextToSpeech");
        tts.say(text);}
};
