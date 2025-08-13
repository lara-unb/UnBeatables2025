#include <behavior/Behavior.hpp>
#include "action/motion/Motion.h"
#include <unistd.h>

Behavior::Behavior() {
    speak = new Speak();
    motion = new Motion();
}

void Behavior::close() const {
    sleep(1);
    motion->rest();
}

void Behavior::process() const{
    motion->wakeUp();
    speak->say("Ola UnBeatables");
}