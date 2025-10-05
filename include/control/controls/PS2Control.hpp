#pragma once

#include <string>
#include <fstream>
#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include "ControlStrategy.hpp"

#define PS2_BUTTON_TRIANGLE   0
#define PS2_BUTTON_CIRCLE     1
#define PS2_BUTTON_CROSS      2
#define PS2_BUTTON_SQUARE     3
#define PS2_BUTTON_L2         4
#define PS2_BUTTON_R2         5
#define PS2_BUTTON_L1         6
#define PS2_BUTTON_R1         7
#define PS2_BUTTON_SELECT     8
#define PS2_BUTTON_START      9
#define PS2_BUTTON_L3         10
#define PS2_BUTTON_R3         11

#define PS2_AXIS_LEFT_X       0
#define PS2_AXIS_LEFT_Y       1
#define PS2_AXIS_RIGHT_X      2
#define PS2_AXIS_RIGHT_Y      3
#define PS2_AXIS_L2           4
#define PS2_AXIS_R2           5
#define PS2_AXIS_COUNT        6

class PS2Control : public ControlStrategy  {
public:
    explicit PS2Control(const std::string& device);
    ~PS2Control() override;

    void open() override;
    void close() override;
    void update() override;
private:
    int fd{};
    std::string device = "/dev/input/js0";
    ControlState state{};
};
