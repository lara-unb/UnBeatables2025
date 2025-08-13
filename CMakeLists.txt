cmake_minimum_required(VERSION 3.10)
project(exe CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BANNER "
  _    _       ____             _        _     _
 | |  | |     |  _ \\           | |      | |   | |
 | |  | |_ __ | |_) | ___  __ _| |_ __ _| |__ | | ___  ___
 | |  | | '_ \\|  _ < / _ \\/ _` | __/ _` | '_ \\| |/ _ \\/ __|
 | |__| | | | | |_) |  __/ (_| | || (_| | |_) | |  __/\\__ \\
  \\____/|_| |_|____/ \\___|\\__,_|\\__\\__,_|_.__/|_|\\___||___/
")

# -----------------------------------------------------------
# Caminho do NAOqi SDK
# -----------------------------------------------------------
set(SDK_PATH "${CMAKE_SOURCE_DIR}/lib/NAOqi/naoqi-sdk-2.8.5.10-linux64"
        CACHE PATH "Path to NAOqi SDK"
)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/lib/NAOqi/naoqi-sdk-2.8.5.10-linux64/include/alcommon/albroker.h")
    message(FATAL_ERROR "NAOqi SDK não encontrado em: ${CMAKE_SOURCE_DIR}/lib/NAOqi/naoqi-sdk-2.8.5.10-linux64")
endif()

# -----------------------------------------------------------
# OpenCV (detecta automaticamente)
# -----------------------------------------------------------
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV não encontrado. Instale libopencv-dev.")
endif()

# -----------------------------------------------------------
# Includes
# -----------------------------------------------------------
include_directories(
        ${SDK_PATH}/include
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

# -----------------------------------------------------------
# Copia arquivos necessários para build
# -----------------------------------------------------------
file(COPY
        ${CMAKE_SOURCE_DIR}/include/perception/cascade
        DESTINATION
        ${CMAKE_BINARY_DIR}/include/perception
)

# -----------------------------------------------------------
# Flags de compilação
# -----------------------------------------------------------
add_compile_options(
        -D_GLIBCXX_USE_CXX11_ABI=0
        -w -Wno-deprecated -Wno-unused-parameter -Wno-unknown-pragmas
        -pthread
)

# -----------------------------------------------------------
# Libs do NAOqi
# -----------------------------------------------------------
link_directories(${SDK_PATH}/lib)
file(GLOB SDK_LIBS "${SDK_PATH}/lib/lib*.so" "${SDK_PATH}/lib/lib*.a")

set(LINK_LIBS "")
foreach(libpath ${SDK_LIBS})
    get_filename_component(libfile ${libpath} NAME)
    string(REGEX REPLACE "^lib(.*)\\.(so|a)$" "\\1" libname ${libfile})
    if(NOT libname STREQUAL "Qt5WebEngineCore")
        list(APPEND LINK_LIBS "-l${libname}")
    endif()
endforeach()

# -----------------------------------------------------------
# config.ini
# -----------------------------------------------------------
add_custom_target(copy_config ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/config.ini"
        "${CMAKE_BINARY_DIR}/config.ini"
)

# -----------------------------------------------------------
# Fontes
# -----------------------------------------------------------
file(GLOB_RECURSE SRC_FILES
        "lib/Logs/EasyLogging.cc"
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        UnBeatables.cpp
)

add_executable(exe ${SRC_FILES})

# -----------------------------------------------------------
# Definições e propriedades
# -----------------------------------------------------------
target_compile_definitions(exe PRIVATE
        USE_NAOQI
        USE_UDP
)

set_target_properties(exe PROPERTIES
        LINK_FLAGS "-Wl,-rpath,${SDK_PATH}/lib"
)

# -----------------------------------------------------------
# Linkagem final
# -----------------------------------------------------------
message(STATUS "${BANNER}")

target_link_libraries(exe
        ${LINK_LIBS}
        ${OpenCV_LIBS}
        pthread
)