cmake_minimum_required(VERSION 3.10)
project(exe CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDK_PATH "${CMAKE_SOURCE_DIR}/lib/NAOqi/naoqi-sdk-2.8.5.10-linux64" CACHE PATH "Path to NAOqi SDK")

include_directories(
        ${SDK_PATH}/include
        /usr/include/opencv4
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

file(COPY
        ${CMAKE_SOURCE_DIR}/include/perception/cascade
        DESTINATION
        ${CMAKE_BINARY_DIR}/include/perception
)

add_compile_options(
        -D_GLIBCXX_USE_CXX11_ABI=0
        -w -Wno-deprecated -Wno-unused-parameter -Wno-unknown-pragmas
        -pthread
)

link_directories(${SDK_PATH}/lib)

file(GLOB_RECURSE SRC_FILES
        "lib/Logs/EasyLogging.cc"
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        UnBeatables.cpp
)

add_executable(exe ${SRC_FILES})

target_compile_definitions(exe PRIVATE USE_NAOQI)

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