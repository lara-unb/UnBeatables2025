#include <behavior/Behavior.hpp>
#include "action/motion/Motion.h"
#include <unistd.h>
#include "UnBoard.hpp"
#include "Logs/EasyLogging.h"

Behavior::Behavior() {
    speak = new Speak();
    motion = new Motion();
    isRunning = true;
}

void Behavior::close() {
    isRunning = false;
    sleep(1);
    motion->rest();
}

void Behavior::process(){
    motion->wakeUp();
    speak->say("Ola UnBeatables");
    while (isRunning) {
        Behavior::gameControllerBehavior();
    }
}

void Behavior::controlCompetitionPhase() {
    if (roboCupControlBoard.competitionPhase == competitionPhase) return;
    competitionPhase = roboCupControlBoard.competitionPhase;

    switch(competitionPhase) {
        case COMPETITION_PHASE_ROUNDROBIN:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Competition Phase: ROUNDROBIN\x1B[0m";
            break;
        case COMPETITION_PHASE_PLAYOFF:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Competition Phase: PLAYOFF\x1B[0m";
            break;
        default:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Competition Phase: UNKNOWN\x1B[0m";
            break;
    }
}

void Behavior::controlCompetitionType() {
    if (roboCupControlBoard.competitionType == competitionType) return;
    competitionType = roboCupControlBoard.competitionType;

    switch(competitionType) {
        case COMPETITION_TYPE_NORMAL:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Competition Type: NORMAL\x1B[0m";
            break;
        case COMPETITION_TYPE_MOST_PASSES:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Competition Type: MOST_PASSES\x1B[0m";
            break;
        default:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Competition Type: UNKNOWN\x1B[0m";
            break;
    }
}

void Behavior::controlGamePhase() {
    if (roboCupControlBoard.gamePhase == gamePhase) return;
    gamePhase = roboCupControlBoard.gamePhase;

    switch(gamePhase) {
        case GAME_PHASE_NORMAL:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game Phase: NORMAL\x1B[0m";
            break;
        case GAME_PHASE_PENALTYSHOOT:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game Phase: PENALTYSHOOT\x1B[0m";
            break;
        case GAME_PHASE_OVERTIME:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game Phase: OVERTIME\x1B[0m";
            break;
        case GAME_PHASE_TIMEOUT:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game Phase: TIMEOUT\x1B[0m";
            break;
        default:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game Phase: UNKNOWN\x1B[0m";
            break;
    }
}

void Behavior::controlState() {
    if (roboCupControlBoard.state == state) return;
    state = roboCupControlBoard.state;

    switch(state) {
        case STATE_INITIAL:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: INITIAL\x1B[0m";
            break;
        case STATE_READY:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: READY\x1B[0m";
            break;
        case STATE_SET:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: SET\x1B[0m";
            break;
        case STATE_PLAYING:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: PLAYING\x1B[0m";
            break;
        case STATE_FINISHED:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: FINISHED\x1B[0m";
            break;
        case STATE_STANDBY:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: STANDBY\x1B[0m";
            break;
        default:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Game State: UNKNOWN\x1B[0m";
            break;
    }
}

void Behavior::controlSetPlay() {
    if (roboCupControlBoard.setPlay == setPlay) return;
    setPlay = roboCupControlBoard.setPlay;

    switch(setPlay) {
        case SET_PLAY_NONE:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: NONE\x1B[0m";
            break;
        case SET_PLAY_GOAL_KICK:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: GOAL_KICK\x1B[0m";
            break;
        case SET_PLAY_PUSHING_FREE_KICK:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: PUSHING_FREE_KICK\x1B[0m";
            break;
        case SET_PLAY_CORNER_KICK:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: CORNER_KICK\x1B[0m";
            break;
        case SET_PLAY_KICK_IN:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: KICK_IN\x1B[0m";
            break;
        case SET_PLAY_PENALTY_KICK:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: PENALTY_KICK\x1B[0m";
            break;
        default:
            LOG(INFO) << "\x1B[34m[BEHAVIOR] Set Play: UNKNOWN\x1B[0m";
            break;
    }
}

void Behavior::gameControllerBehavior() {
    controlCompetitionPhase();
    controlCompetitionType();
    controlGamePhase();
    controlState();
    controlSetPlay();
}