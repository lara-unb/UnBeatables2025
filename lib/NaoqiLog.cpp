#include <alcommon/albroker.h>

void customNaoqiLogHandler(
    const qi::LogLevel level,
    const boost::chrono::time_point<qi::Clock> date,
    const boost::chrono::time_point<qi::SystemClock> systemDate,
    const char* category,
    const char* msg,
    const char* file,
    const char* function,
    const int line
){
    std::string levelStr;
    switch (level) {
        case qi::LogLevel_Debug:   levelStr = "[D]"; break;
        case qi::LogLevel_Info:    levelStr = "[I]"; break;
        case qi::LogLevel_Warning: levelStr = "[W]"; break;
        case qi::LogLevel_Error:   levelStr = "[E]"; break;
        case qi::LogLevel_Fatal:   levelStr = "[F]"; break;
        default:                   levelStr = "[?]"; break;
    }

    std::stringstream logMessage;
    logMessage << "\033[33m" << "[NAOqi] " << levelStr << " " << msg << " (" << category << ")" << "\033[0m";

    switch (level) {
        case qi::LogLevel_Debug:
            LOG(DEBUG) << logMessage.str();
            break;
        case qi::LogLevel_Info:
            LOG(INFO) << logMessage.str();
            break;
        case qi::LogLevel_Warning:
            LOG(WARNING) << logMessage.str();
            break;
        case qi::LogLevel_Error:
        case qi::LogLevel_Fatal:
            LOG(ERROR) << logMessage.str();
            break;
        default:
            LOG(INFO) << logMessage.str();
            break;
    }
}

void redirectNaoqiLogsToEasyLogging() {
    qi::log::setLogLevel(qi::LogLevel_Silent);
    qi::log::removeHandler("console");
    qi::log::addHandler("easylogging_redirector", customNaoqiLogHandler);
}