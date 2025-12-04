cmake_minimum_required(VERSION 3.12)

#-----------------------------------------------------------------
# Project Definition
#-----------------------------------------------------------------

project(Jaymod
    VERSION 2.2.0
    LANGUAGES C CXX
)

message(STATUS "")
message(STATUS "====================================")
message(STATUS "  Jaymod v${PROJECT_VERSION}")
message(STATUS "  Modern CMake Build System")
message(STATUS "====================================")
message(STATUS "")

#-----------------------------------------------------------------
# CMake Configuration
#-----------------------------------------------------------------

# Set module path for custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#-----------------------------------------------------------------
# Build Options
#-----------------------------------------------------------------

option(CROSS_COMPILE32 "Force 32-bit compilation on 64-bit systems" OFF)
option(BUILD_QAGAME "Build qagame server module" ON)
option(BUILD_CGAME "Build cgame client module" ON)
option(BUILD_UI "Build ui interface module" ON)
option(BUILD_MOD_PK3 "Package modules into PK3 file" ON)

# Include cross-compilation support first (before platform detection)
include(JaymodCrossCompile32)

# Include platform detection and compiler configuration
include(JaymodPlatform)

# Include feature setup
include(JaymodSetupFeatures)

# Include module building functions
include(JaymodBuildMod)

#-----------------------------------------------------------------
# Source Directories
#-----------------------------------------------------------------

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(GAME_DIR "${SRC_DIR}/game")
set(CGAME_DIR "${SRC_DIR}/cgame")
set(UI_DIR "${SRC_DIR}/ui")
set(BGAME_DIR "${SRC_DIR}/bgame")
set(BASE_DIR "${SRC_DIR}/base")
set(LUA_DIR "${SRC_DIR}/lua")
set(OMNIBOT_DIR "${SRC_DIR}/Omnibot")

# Common include directories
set(COMMON_INCLUDES
    ${CMAKE_BINARY_DIR}
    ${SRC_DIR}
    ${BGAME_DIR}
    ${BASE_DIR}
)

#-----------------------------------------------------------------
# Generate Project Header
#-----------------------------------------------------------------

# Generate base/project.h from project/info.py at configure time
find_package(Python3 REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/base)

execute_process(
    COMMAND ${Python3_EXECUTABLE} info.py -h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/project
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/base/project.h
    RESULT_VARIABLE GENERATE_PROJECT_RESULT
)

if(NOT GENERATE_PROJECT_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to generate base/project.h")
endif()

message(STATUS "Generated base/project.h")

#-----------------------------------------------------------------
# Lua Library (bundled)
#-----------------------------------------------------------------

if(FEATURE_LUA)
    file(GLOB LUA_SOURCES
        "${LUA_DIR}/lapi.c"
        "${LUA_DIR}/lcode.c"
        "${LUA_DIR}/ldebug.c"
        "${LUA_DIR}/ldo.c"
        "${LUA_DIR}/ldump.c"
        "${LUA_DIR}/lfunc.c"
        "${LUA_DIR}/lgc.c"
        "${LUA_DIR}/llex.c"
        "${LUA_DIR}/lmem.c"
        "${LUA_DIR}/lobject.c"
        "${LUA_DIR}/lopcodes.c"
        "${LUA_DIR}/lparser.c"
        "${LUA_DIR}/lstate.c"
        "${LUA_DIR}/lstring.c"
        "${LUA_DIR}/ltable.c"
        "${LUA_DIR}/ltm.c"
        "${LUA_DIR}/lundump.c"
        "${LUA_DIR}/lvm.c"
        "${LUA_DIR}/lzio.c"
        "${LUA_DIR}/lauxlib.c"
        "${LUA_DIR}/lbaselib.c"
        "${LUA_DIR}/ldblib.c"
        "${LUA_DIR}/liolib.c"
        "${LUA_DIR}/lmathlib.c"
        "${LUA_DIR}/loslib.c"
        "${LUA_DIR}/ltablib.c"
        "${LUA_DIR}/lstrlib.c"
        "${LUA_DIR}/loadlib.c"
        "${LUA_DIR}/linit.c"
    )

    add_library(lua STATIC ${LUA_SOURCES})
    target_include_directories(lua PUBLIC ${LUA_DIR})

    # Lua uses C++ features, so compile as C++
    set_source_files_properties(${LUA_SOURCES} PROPERTIES LANGUAGE CXX)
endif()

#-----------------------------------------------------------------
# Base Library (common utilities)
#-----------------------------------------------------------------

file(GLOB BASE_SOURCES
    "${BASE_DIR}/base64/*.cpp"
    "${BASE_DIR}/lua/*.cpp"
    "${BASE_DIR}/str/*.cpp"
    "${BASE_DIR}/text/*.cpp"
)

add_library(base STATIC ${BASE_SOURCES})
target_include_directories(base PUBLIC ${SRC_DIR} ${CMAKE_BINARY_DIR})
if(FEATURE_LUA)
    target_link_libraries(base PUBLIC lua)
endif()

#-----------------------------------------------------------------
# Background Game (shared between client and server)
#-----------------------------------------------------------------

file(GLOB BGAME_SOURCES
    "${BGAME_DIR}/*.c"
    "${BGAME_DIR}/*.cpp"
    "${BGAME_DIR}/cvar/*.cpp"
    "${BGAME_DIR}/str/*.cpp"
)

# Platform-specific sources
if(WIN32)
    file(GLOB BGAME_PLATFORM_SOURCES "${BGAME_DIR}/win32/*.cpp")
elseif(UNIX AND NOT APPLE)
    file(GLOB BGAME_PLATFORM_SOURCES "${BGAME_DIR}/linux/*.cpp")
elseif(APPLE)
    file(GLOB BGAME_PLATFORM_SOURCES "${BGAME_DIR}/osx/*.cpp")
endif()

list(APPEND BGAME_SOURCES ${BGAME_PLATFORM_SOURCES})

# Note: bgame sources are compiled into each module, not as a separate library
# Each module defines its own CGAMEDLL, GAMEDLL, or UIDLL flag

#-----------------------------------------------------------------
# Server Game Module (qagame)
#-----------------------------------------------------------------

if(BUILD_QAGAME)
    file(GLOB QAGAME_SOURCES
        "${GAME_DIR}/g_*.cpp"
    )

    # Platform-specific sources
    if(WIN32)
        file(GLOB QAGAME_PLATFORM_SOURCES "${GAME_DIR}/win32/*.cpp")
    elseif(UNIX AND NOT APPLE)
        file(GLOB QAGAME_PLATFORM_SOURCES "${GAME_DIR}/linux/*.cpp")
    endif()

    list(APPEND QAGAME_SOURCES ${QAGAME_PLATFORM_SOURCES})

    # Omnibot integration (C++ files)
    set(QAGAME_OMNIBOT_SOURCES "")
    if(FEATURE_OMNIBOT)
        list(APPEND QAGAME_OMNIBOT_SOURCES
            "${GAME_DIR}/g_etbot_interface.cpp"
            "${OMNIBOT_DIR}/Common/BotLoadLibrary.cpp"
        )
    endif()

    # Build the module
    build_game_module(qagame
        SOURCES ${QAGAME_SOURCES} ${BGAME_SOURCES} ${QAGAME_OMNIBOT_SOURCES}
        DEFINITIONS GAMEDLL $<$<BOOL:${FEATURE_OMNIBOT}>:FEATURE_OMNIBOT>
        INCLUDES ${COMMON_INCLUDES} ${GAME_DIR} ${BGAME_DIR} ${UI_DIR} ${OMNIBOT_DIR}
        LIBRARIES base
    )

    # Link platform-specific libraries
    if(WIN32)
        target_link_libraries(qagame PRIVATE ws2_32 iphlpapi advapi32)
    elseif(UNIX)
        target_link_libraries(qagame PRIVATE m dl)
    endif()
endif()

#-----------------------------------------------------------------
# Client Game Module (cgame)
#-----------------------------------------------------------------

if(BUILD_CGAME)
    file(GLOB CGAME_SOURCES
        "${CGAME_DIR}/cg_*.c"
        "${CGAME_DIR}/cg_*.cpp"
        "${CGAME_DIR}/cvar/*.cpp"
    )

    # Platform-specific sources
    if(WIN32)
        file(GLOB CGAME_PLATFORM_SOURCES "${CGAME_DIR}/win32/*.cpp")
    elseif(UNIX AND NOT APPLE)
        file(GLOB CGAME_PLATFORM_SOURCES "${CGAME_DIR}/linux/*.cpp")
    endif()

    list(APPEND CGAME_SOURCES ${CGAME_PLATFORM_SOURCES})

    # UI shared sources (cgame uses some UI code)
    file(GLOB CGAME_UI_SOURCES "${UI_DIR}/ui_shared.cpp")
    list(APPEND CGAME_SOURCES ${CGAME_UI_SOURCES})

    # Build the module
    build_game_module(cgame
        SOURCES ${CGAME_SOURCES} ${BGAME_SOURCES}
        DEFINITIONS CGAMEDLL
        INCLUDES ${COMMON_INCLUDES} ${CGAME_DIR} ${BGAME_DIR} ${UI_DIR}
        LIBRARIES base
    )

    # Link platform-specific libraries
    if(UNIX AND NOT WIN32)
        target_link_libraries(cgame PRIVATE m)
    endif()
endif()

#-----------------------------------------------------------------
# UI Module
#-----------------------------------------------------------------

if(BUILD_UI)
    file(GLOB UI_SOURCES
        "${UI_DIR}/ui_*.c"
        "${UI_DIR}/ui_*.cpp"
        "${UI_DIR}/ui_shared.cpp"
    )

    # Platform-specific sources
    if(WIN32)
        file(GLOB UI_PLATFORM_SOURCES "${UI_DIR}/win32/*.cpp")
    elseif(UNIX AND NOT APPLE)
        file(GLOB UI_PLATFORM_SOURCES "${UI_DIR}/linux/*.cpp")
    endif()

    list(APPEND UI_SOURCES ${UI_PLATFORM_SOURCES})

    # Build the module
    build_game_module(ui
        SOURCES ${UI_SOURCES} ${BGAME_SOURCES}
        DEFINITIONS UIDLL
        INCLUDES ${COMMON_INCLUDES} ${UI_DIR} ${BGAME_DIR}
        LIBRARIES base
    )

    # Link platform-specific libraries
    if(UNIX AND NOT WIN32)
        target_link_libraries(ui PRIVATE m)
    endif()
endif()

#-----------------------------------------------------------------
# Build Summary
#-----------------------------------------------------------------

message(STATUS "")
message(STATUS "Build Summary:")
message(STATUS "  qagame:    ${BUILD_QAGAME}")
message(STATUS "  cgame:     ${BUILD_CGAME}")
message(STATUS "  ui:        ${BUILD_UI}")
message(STATUS "  Omnibot:   ${FEATURE_OMNIBOT}")
message(STATUS "  Lua:       ${FEATURE_LUA}")
message(STATUS "  PK3:       ${BUILD_MOD_PK3}")
message(STATUS "")
message(STATUS "Output directory: ${CMAKE_BINARY_DIR}/jaymod-${PROJECT_VERSION}")
message(STATUS "")
