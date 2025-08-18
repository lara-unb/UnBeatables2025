#pragma once 

#include <alproxies/alledsproxy.h>
#include <string>

class SetLeds{
    private:
        AL::ALLedsProxy leds;

    public:

        SetLeds: ();

        ~SetLeds: ();
        
        void fadeRGB (const std:: string&name, const std:: string& color){leds.fadeRGB(name, color, 0.01f)}
        
}
