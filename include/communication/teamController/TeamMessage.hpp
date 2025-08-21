#pragma once

#include <stdint.h>
#define MAX_ROBOTS      5

struct TeamMessage {
    uint8_t playerNumber = 1;
    char header[4] = {'T', 'E', 'S', 'T'};
};

extern TeamMessage selfMessage;
extern TeamMessage teamMessages[MAX_ROBOTS];