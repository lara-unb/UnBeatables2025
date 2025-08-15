#pragma once

#include "perception/Perception.hpp"
#include "behavior/Behavior.hpp"
#include "communication/Communication.hpp"
#include "Builder.hpp"

class UnBeatables {
private:
    Builder *builder;

    Perception* perception;
    Behavior* behavior;
    Communication* communication;

    void initSession();

public:
    UnBeatables();
	void close() const;
	void process() const;
};
