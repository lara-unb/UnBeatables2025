#!/usr/bin/env python
# -*- coding:utf-8 -*-
# https:

from construct import Byte, Struct, Enum, Bytes, Const, Array, Int16ul, Int32ul, PaddedString, Flag, Int16sl

RobotInfo = "robot_info" / Struct(
    "penalty" / Enum(Byte,
                     PENALTY_NONE=0,
                     PENALTY_SPL_ILLEGAL_BALL_CONTACT=1,
                     PENALTY_SPL_PLAYER_PUSHING=2,
                     PENALTY_SPL_ILLEGAL_MOTION_IN_SET=3,
                     PENALTY_SPL_INACTIVE_PLAYER=4,
                     PENALTY_SPL_ILLEGAL_DEFENDER=5,
                     PENALTY_SPL_LEAVING_THE_FIELD=6,
                     PENALTY_SPL_KICK_OFF_GOAL=7,
                     PENALTY_SPL_REQUEST_FOR_PICKUP=8,
                     PENALTY_SPL_LOCAL_GAME_STUCK=9,
                     PENALTY_SPL_ILLEGAL_POSITIONING=10),
    # ),
    "secs_till_unpenalized" / Byte)

TeamInfo = "team" / Struct(
    "team_number" / Byte,
    "team_color" / Enum(Byte,
                        TEAM_BLUE=0,
                        TEAM_RED=1,
                        TEAM_YELLOW=2,
                        TEAM_BLACK=3,
                        TEAM_WHITE=4,
                        TEAM_GREEN=5,
                        TEAM_ORANGE=6,
                        TEAM_PURPLE=7,
                        TEAM_BROWN=8,
                        TEAM_GRAY=9),
    "score" / Byte,
    "penalty_shot" / Byte,  # penalty shot counter
    "single_shots" / Int16ul,  # bits represent penalty shot success
    "players" / Array(6, RobotInfo))

GameState = "gamedata" / Struct(
    "header" / Const(b'RGme'),
    "version" / Const(12, Byte),
    "packet_number" / Byte,
    "players_per_team" / Byte,
    "competitionPhase" /
    Enum(Byte, COMPETITION_PHASE_ROUNDROBIN=0, COMPETITION_PHASE_PLAYOFF=1),
    "competitionType" /
    Enum(Byte, COMPETITION_TYPE_NORMAL=0, COMPETITION_TYPE_MIXEDTEAM=1),
    "gamePhase" / Enum(Byte,
                       GAME_PHASE_NORMAL=0,
                       GAME_PHASE_PENALTYSHOOT=1,
                       GAME_PHASE_OVERTIME=2,
                       GAME_PHASE_TIMEOUT=3),
    "game_state" / Enum(
        Byte,
        STATE_INITIAL=0,
        # auf startposition gehen
        STATE_READY=1,
        # bereithalten
        STATE_SET=2,
        # spielen
        STATE_PLAYING=3,
        # spiel zu ende
        STATE_FINISHED=4),
    "setPlay" / Enum(Byte,
                     SET_PLAY_NONE=0,
                     SET_PLAY_GOAL_FREE_KICK=1,
                     SET_PLAY_PUSHING_FREE_KICK=2,
                     SET_PLAY_CORNER_KICK=3,
                     SET_PLAY_KICK_IN=4),
    "first_half" / Flag,
    "kickingTeam" / Byte,
    "secsRemaining" / Int16ul,
    "secondaryTime" / Int16ul,
    "teams" / Array(2, "team" / TeamInfo),
)

GAME_CONTROLLER_RESPONSE_VERSION = 3

ReturnData = Struct("header" / Const(b"RGrt"), "version" / Const(3, Byte),
                    "team" / Byte, "player" / Byte, "message" / Byte)
