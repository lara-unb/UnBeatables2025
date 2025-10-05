#include <behavior/Behavior.hpp>
#include "action/motion/Motion.h"
#include <unistd.h>
#include "UnBoard.hpp"
#include "Logs/EasyLogging.h"
#include <control/ControlBoard.h>

#include <chrono>
#include <thread>
#include <cmath>

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
    const int ENTER_THRESHOLD = 9000;
    const int EXIT_THRESHOLD  = 7000;
    const float SMOOTH_ALPHA  = 0.20f;
    const std::chrono::milliseconds LOOP_MS(20);

    bool moving = false;
    bool rotating = false;
    bool headMoving = false;
    float smoothLX = 0.0f, smoothLY = 0.0f;
    float smoothRX = 0.0f, smoothRY = 0.0f;

    while (isRunning) {
        int16_t lx = controlState.leftStickX;
        int16_t ly = controlState.leftStickY;
        int16_t rx = controlState.rightStickX;
        int16_t ry = controlState.rightStickY;
        bool r1 = controlState.r1;
        bool l1 = controlState.l1;

        if (std::abs((int)rx) > ENTER_THRESHOLD || std::abs((int)ry) > ENTER_THRESHOLD) {
            float nx = rx / 32767.0f;
            float ny = ry / 32767.0f;
            smoothRX = SMOOTH_ALPHA * nx + (1.0f - SMOOTH_ALPHA) * smoothRX;
            smoothRY = SMOOTH_ALPHA * ny + (1.0f - SMOOTH_ALPHA) * smoothRY;

            motion->moveHead(smoothRX, smoothRY);
            headMoving = true;
        } else if (headMoving) {
            motion->stopMoveHead();
            headMoving = false;
        }

        int abs_lx = std::abs((int)lx);
        int abs_ly = std::abs((int)ly);

        if (abs_lx > ENTER_THRESHOLD || abs_ly > ENTER_THRESHOLD) {
            moving = true;
        } else if (abs_lx < EXIT_THRESHOLD && abs_ly < EXIT_THRESHOLD) {
            moving = false;
        }

        float normLX = lx / 32767.0f;
        float normLY = ly / 32767.0f;
        smoothLX = SMOOTH_ALPHA * normLX + (1.0f - SMOOTH_ALPHA) * smoothLX;
        smoothLY = SMOOTH_ALPHA * normLY + (1.0f - SMOOTH_ALPHA) * smoothLY;

        if (moving) {
            LOG(INFO) << "[MOVE] raw(" << lx << "," << ly << ") norm(" << normLX << "," << normLY
                      << ") smooth(" << smoothLX << "," << smoothLY << ")";
            motion->move(smoothLX, smoothLY);
        } else {
            motion->stopMove();
        }

        if (r1 && !l1) {
            motion->rotate(true);
            rotating = true;
        } else if (l1 && !r1) {
            motion->rotate(false);
            rotating = true;
        } else if (rotating) {
            motion->stopRotate();
            rotating = false;
        }

        std::this_thread::sleep_for(LOOP_MS);
    }
}

void Behavior::controlerCompetitionPhase() {
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

void Behavior::controlerCompetitionType() {
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

void Behavior::controlerGamePhase() {
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

void Behavior::controlerState() {
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

void Behavior::controlerSetPlay() {
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
    controlerCompetitionPhase();
    controlerCompetitionType();
    controlerGamePhase();
    controlerState();
    controlerSetPlay();
}