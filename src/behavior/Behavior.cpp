#include <behavior/Behavior.hpp>

Behavior::Behavior() {
    speak = new Speak();
}

Behavior::~Behavior() {
    speak->close();
}

void Behavior::close() {
    speak->close();
}

void Behavior::process() {
    speak->say("Olá UnBeatables");
}