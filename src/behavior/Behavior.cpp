#include <behavior/Behavior.hpp>
#include <unistd.h>
#include "action/motion/Motion.h"

Behavior::Behavior() {
    // speak = new Speak();
    motion = new Motion();
}

void Behavior::close() {
    // speak->close();
    sleep(1);
    motion->rest();
}

void Behavior::process() const{
    motion->wakeUp();
    // speak->say("i");
}