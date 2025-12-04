#-----------------------------------------------------------------
# Feature Setup
#-----------------------------------------------------------------

include(CMakeDependentOption)

# Omnibot support - enabled by default on Linux and Windows (not MinGW unless forced)
cmake_dependent_option(FEATURE_OMNIBOT
    "Enable Omni-bot support for qagame module"
    ON
    "(NOT MINGW AND WIN32) OR CMAKE_SYSTEM_NAME MATCHES Linux OR FORCE_OMNIBOT"
    OFF
)

if(FEATURE_OMNIBOT)
    message(STATUS "Omni-bot support: ENABLED")
else()
    message(STATUS "Omni-bot support: DISABLED")
endif()

# Lua support (Jaymod uses Lua for scripting)
option(FEATURE_LUA "Enable Lua scripting support" ON)

if(FEATURE_LUA)
    message(STATUS "Lua scripting: ENABLED")
else()
    message(STATUS "Lua scripting: DISABLED")
endif()

# Build options
option(BUILD_QAGAME "Build qagame (server-side game module)" ON)
option(BUILD_CGAME "Build cgame (client-side game module)" ON)
option(BUILD_UI "Build ui (user interface module)" ON)
option(BUILD_MOD_PK3 "Build mod PK3 archive" ON)

# Development options
option(DEBUG_MEMORY "Enable memory debugging" OFF)
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
