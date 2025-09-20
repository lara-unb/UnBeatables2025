#pragma once

#include <alproxies/alledsproxy.h>
#include <string>

#define LED_RED     "0x00FF0000"
#define LED_GREEN   "0x0000FF00"
#define LED_BLUE    "0x000000FF"
#define LED_WHITE   "0x00FFFFFF"

class Leds {
    private: 
        AL::ALLedsProxy leds;
        void fadeRGB (const std::string& name, const std::string& color);

    public:
        Leds();
        ~Leds();

        void setEyeLeds (const std::string& color);
        void setRightEyeLeds (const std::string& color);
        void setLeftEyeLeds (const std::string& color);
        void setChestLeds (const std::string& color);
        void setFeetLeds (const std::string& color);
        void setRightFootLeds (const std::string& color);
        void setLeftFootLeds (const std::string& color);
};
