#include <action/leds/Leds.h>
#include <alcommon/alproxy.h>
#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"

Leds::Leds()
    : leds(boost::make_shared<AL::ALProxy>(session, "ALLeds"))
{
    LOG(INFO) << "\x1B[37m[LEDS] Started successfully\x1B[0m";
}

void Leds::fadeRGB(const std::string& name, const std::string& color) {
    try {
        // Converte string hexa para int
        int rgb = std::stoi(color, nullptr, 16);
        float duration = 1.0f;

        leds.fadeRGB(name, rgb, duration);

        LOG(INFO) << "\x1B[32m[LEDS] " << name
                  << " setado para cor " << color << "\x1B[0m";
    } catch (const std::exception& e) {
        LOG(ERROR) << "[LEDS] Erro em fadeRGB: " << e.what();
    }
}


// ===== Métodos de LEDs =====

void Leds::setEyeLeds(const std::string& color){
    Leds::fadeRGB("FaceLeds", color);
}

void Leds::setRightEyeLeds(const std::string& color){
    Leds::fadeRGB("RightFaceLeds", color);
}

void Leds::setLeftEyeLeds(const std::string& color){
    Leds::fadeRGB("LeftFaceLeds", color);
}

void Leds::setChestLeds(const std::string& color){
    Leds::fadeRGB("ChestLeds", color);
}

void Leds::setFeetLeds(const std::string& color){
    Leds::fadeRGB("FeetLeds", color);
}

void Leds::setRightFootLeds(const std::string& color){
    Leds::fadeRGB("RightFootLeds", color);
}

void Leds::setLeftFootLeds(const std::string& color){
    Leds::fadeRGB("LeftFootLeds", color);
}
