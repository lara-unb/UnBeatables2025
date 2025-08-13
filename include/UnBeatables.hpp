#progma once

#include "UnBoard.hpp"
#include "ConnectionConfig.hpp"

#include "perception/Perception.hpp"
#include "behavior/Behavior.hpp"
#include "communication/Communication.hpp"

class UnBeatables {
private:
    NAOqiAddress naoqiAddress;
    GameControllerAddress gameControllerAddress;
    qi::SessionPtr session;

    PerceptionBoard perceptionBoard;
    CommunicationBoard communicationBoard;

    std::shared_ptr<Perception> perception;
    std::shared_ptr<Behavior> behavior;
    std::shared_ptr<Communication> communication;

	void setConfig();

	void initSession();
	void initCommunication();
	void initPerception();
	void initBehavior();
public:
    UnBeatables();
	void close();
	void process();
};
