#pragma once

#include <string>
#include <behavior/Behavior.hpp>
#include <communication/Communication.hpp>
#include <perception/Perception.hpp>
#include <control/ControlsManager.hpp>

#define NAOQI_CAMERA 		1
#define V4L2_CAMERA			2

struct SystemSettings {
	int camera;
	std::string cascade;
};
extern SystemSettings systemSettings;

class Builder {
public:
	Behavior* buildBehavior();
	Perception* buildPerception();
	Communication* buildCommunication();
	ControlsManager* buildControlManager();
};