#pragma once

#include "Builder.hpp"
#include "perception/Perception.hpp"
#include "behavior/Behavior.hpp"
#include "communication/Communication.hpp"

class UnBeatables {
private:
    Builder *builder;
    Perception* perception;
    Behavior* behavior;
    Communication* communication;
    ControlsManager* controlManager;
    void initSession();
public:
    UnBeatables();
	void close() const;
	void process() const;
};
