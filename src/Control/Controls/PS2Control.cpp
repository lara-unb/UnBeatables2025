#include "control/controls/PS2Control.hpp"
#include "Logs/EasyLogging.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

PS2Control::PS2Control(const std::string& device)
    : device(device) {
    PS2Control::open();
    LOG(INFO) << "\x1B[33m[PS2CONTROLLER] Connected to " << device << "\x1B[0m";
}

PS2Control::~PS2Control() {
    LOG(INFO) << "\x1B[33m[PS2CONTROLLER] Closing " << device << "\x1B[0m";
    PS2Control::close();
}

void PS2Control::open() {
    fd = ::open(device.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        throw std::runtime_error("Failed to open joystick device: " + device);
    }
}

void PS2Control::close() {
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

void PS2Control::update() {
    js_event event;
    if (read(fd, &event, sizeof(event)) > 0) {
        event.type &= ~JS_EVENT_INIT;

        if (event.type == JS_EVENT_BUTTON) {
            const char* status = event.value ? "PRESSED" : "RELEASED";
            switch (event.number) {
                case PS2_BUTTON_SELECT:   state.select = event.value;   LOG(INFO) << "\x1B[33m[PS2CONTROLLER] SELECT " << status << "\x1B[0m"; break;
                case PS2_BUTTON_L3:       state.l3 = event.value;       LOG(INFO) << "\x1B[33m[PS2CONTROLLER] L3 " << status << "\x1B[0m"; break;
                case PS2_BUTTON_R3:       state.r3 = event.value;       LOG(INFO) << "\x1B[33m[PS2CONTROLLER] R3 " << status << "\x1B[0m"; break;
                case PS2_BUTTON_START:    state.start = event.value;    LOG(INFO) << "\x1B[33m[PS2CONTROLLER] START " << status << "\x1B[0m"; break;
                case PS2_BUTTON_L2:       state.l2 = event.value;       LOG(INFO) << "\x1B[33m[PS2CONTROLLER] L2 " << status << "\x1B[0m"; break;
                case PS2_BUTTON_R2:       state.r2 = event.value;       LOG(INFO) << "\x1B[33m[PS2CONTROLLER] R2 " << status << "\x1B[0m"; break;
                case PS2_BUTTON_L1:       state.l1 = event.value;       LOG(INFO) << "\x1B[33m[PS2CONTROLLER] L1 " << status << "\x1B[0m"; break;
                case PS2_BUTTON_R1:       state.r1 = event.value;       LOG(INFO) << "\x1B[33m[PS2CONTROLLER] R1 " << status << "\x1B[0m"; break;
                case PS2_BUTTON_TRIANGLE: state.triangle = event.value; LOG(INFO) << "\x1B[33m[PS2CONTROLLER] TRIANGLE " << status << "\x1B[0m"; break;
                case PS2_BUTTON_CIRCLE:   state.circle = event.value;   LOG(INFO) << "\x1B[33m[PS2CONTROLLER] CIRCLE " << status << "\x1B[0m"; break;
                case PS2_BUTTON_CROSS:    state.cross = event.value;    LOG(INFO) << "\x1B[33m[PS2CONTROLLER] CROSS " << status << "\x1B[0m"; break;
                case PS2_BUTTON_SQUARE:   state.square = event.value;   LOG(INFO) << "\x1B[33m[PS2CONTROLLER] SQUARE " << status << "\x1B[0m"; break;
                default: break;
            }
        }
        else if (event.type == JS_EVENT_AXIS) {
            switch (event.number) {
                case PS2_AXIS_LEFT_X:
                    state.leftStickX = event.value;
                    // LOG(INFO) << "\x1B[33m[PS2CONTROLLER] LEFT STICK X = " << event.value << "\x1B[0m";
                    break;
                case PS2_AXIS_LEFT_Y:
                    state.leftStickY = event.value;
                    // LOG(INFO) << "\x1B[33m[PS2CONTROLLER] LEFT STICK Y = " << event.value << "\x1B[0m";
                    break;
                case PS2_AXIS_RIGHT_X:
                    state.rightStickX = event.value;
                    // LOG(INFO) << "\x1B[33m[PS2CONTROLLER] RIGHT STICK X = " << event.value << "\x1B[0m";
                    break;
                case PS2_AXIS_RIGHT_Y:
                    state.rightStickY = event.value;
                    // LOG(INFO) << "\x1B[33m[PS2CONTROLLER] RIGHT STICK Y = " << event.value << "\x1B[0m";
                    break;
                default: break;
            }
        }
    }
}

void PS2Control::printState() const {
    LOG(INFO) << "\x1B[33m[PS2CONTROLLER] "
              << "LX=" << state.leftStickX
              << " LY=" << state.leftStickY
              << " RX=" << state.rightStickX
              << " RY=" << state.rightStickY
              << " | X=" << state.cross
              << " O=" << state.circle
              << " △=" << state.triangle
              << " ☐=" << state.square
              << " | START=" << state.start
              << " SELECT=" << state.select
              << "\x1B[0m";
}
