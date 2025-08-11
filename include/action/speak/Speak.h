#pragma once

#include <alproxies/altexttospeechproxy.h>
#include <string>

class Speak{
private:
    AL::ALTextToSpeechProxy speakService;

public:
    Speak();
    ~Speak();

    void open();
    void close();
    void say(const std::string &text);
};
