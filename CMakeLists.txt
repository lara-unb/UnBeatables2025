cmake_minimum_required(VERSION 3.10)
project(exe CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDK_PATH "$ENV{HOME}/UnBeatables/naoqi-sdk-2.8.5.10-linux64" CACHE PATH "Path to NAOqi SDK")

include_directories(
        ${SDK_PATH}/include
        /usr/include/opencv4
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

add_compile_options(
        -D_GLIBCXX_USE_CXX11_ABI=0
        -w -Wno-deprecated -Wno-unused-parameter -Wno-unknown-pragmas
        -pthread
)

link_directories(${SDK_PATH}/lib)

file(GLOB SRC_FILES "*.cpp" "lib/EasyLogging.cc")

add_executable(exe ${SRC_FILES})

set_target_properties(exe PROPERTIES
        LINK_FLAGS "-Wl,-rpath,${SDK_PATH}/lib"
)

file(GLOB SDK_LIBS "${SDK_PATH}/lib/lib*.so" "${SDK_PATH}/lib/lib*.a")

set(LINK_LIBS "")

foreach(libpath ${SDK_LIBS})
    get_filename_component(libfile ${libpath} NAME)
    string(REGEX REPLACE "^lib(.*)\\.(so|a)$" "\\1" libname ${libfile})

    if(NOT libname STREQUAL "Qt5WebEngineCore")
        list(APPEND LINK_LIBS "-l${libname}")
    endif()
endforeach()

target_link_libraries(exe ${LINK_LIBS}
        -lopencv_core -lopencv_highgui -lopencv_imgproc pthread
)