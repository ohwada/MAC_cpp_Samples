## https://github.com/gammasoft71/Examples_wxWidgets/tree/master/src/HelloWorlds/wxWidgetsHelloWorld

cmake_minimum_required(VERSION 3.0)
project(wxWidgetsHelloWorld)


find_package(wxWidgets 3.1.4 REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCES wxWidgetsHelloWorld.cpp)

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "HelloWorlds")
