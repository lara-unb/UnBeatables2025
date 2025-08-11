#pragma once

#include <alproxies/altexttospeechproxy.h>
#include <string>

class Speak{
private:
    AL::ALTextToSpeechProxy speakService;

public:
    Speak();
    ~Speak();

    void say(const std::string &text);
};
