#pragma once
    
#include "SetLeds.h"
#include <string>

class Leds {
    private: 
        SetLeds leds;

    public:
        Leds();
        ~Leds();


        void SetEyeLeds (const std::string& color);
        void SetRightEyeLeds (const std::string& color);
        void SetLeftEyeLeds (const std::string& color);
        void SetChestLeds (const std::string& color);
        void SetFeetLeds (const std::string& color);
        void SetRightFootLeds (const std::string& color);
        void SetLeftFootLeds (const std::string& color);
};
