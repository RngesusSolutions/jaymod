#-----------------------------------------------------------------
# Platform Detection and Compiler Configuration
#-----------------------------------------------------------------

# Detect architecture
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(JAYMOD_64BITS TRUE)
    set(JAYMOD_32BITS FALSE)
else()
    set(JAYMOD_64BITS FALSE)
    set(JAYMOD_32BITS TRUE)
endif()

# Detect processor type
if(CMAKE_SYSTEM_PROCESSOR MATCHES "i.86|x86|X86|amd64|AMD64|x86_64")
    set(JAYMOD_X86 TRUE)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
    set(JAYMOD_ARM TRUE)
endif()

# Set architecture string for binary naming
if(JAYMOD_X86 AND JAYMOD_32BITS)
    if(WIN32)
        set(ARCH "x86")
    else()
        set(ARCH "i386")
    endif()
elseif(JAYMOD_X86 AND JAYMOD_64BITS)
    if(WIN32)
        set(ARCH "x64")
    else()
        set(ARCH "x86_64")
    endif()
elseif(JAYMOD_ARM AND JAYMOD_64BITS)
    set(ARCH "aarch64")
elseif(JAYMOD_ARM AND JAYMOD_32BITS)
    set(ARCH "armhf")
endif()

# Set library naming conventions based on platform
if(UNIX AND NOT APPLE)
    set(LIB_PREFIX "")
    set(LIB_SUFFIX ".mp.${ARCH}")
    set(LIB_EXT ".so")
elseif(APPLE)
    set(LIB_PREFIX "")
    set(LIB_SUFFIX "_mac")
    set(LIB_EXT ".dylib")
elseif(WIN32)
    set(LIB_PREFIX "")
    set(LIB_SUFFIX "_mp_${ARCH}")
    set(LIB_EXT ".dll")
endif()

message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Architecture: ${ARCH} (${CMAKE_SIZEOF_VOID_P}-byte pointers)")
message(STATUS "Module naming: <name>${LIB_SUFFIX}${LIB_EXT}")

#-----------------------------------------------------------------
# Compiler Flags
#-----------------------------------------------------------------

# Enable colored diagnostics
if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

# Common flags for Unix-like systems
if(UNIX)
    # 32-bit compilation on 64-bit system (if CROSS_COMPILE32)
    if(JAYMOD_32BITS AND CMAKE_SIZEOF_VOID_P EQUAL 4)
        add_compile_options(-m32)
        add_link_options(-m32)
    endif()

    # Optimization
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffast-math")

    # Debug symbols
    if(CMAKE_C_COMPILER_ID MATCHES "GNU")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")
    endif()

    # Visibility
    add_compile_options(-fvisibility=hidden)

    # Static linking for MinGW
    if(MINGW)
        add_link_options(-static-libgcc -static-libstdc++)
    endif()
endif()

# Windows MSVC flags
if(MSVC)
    add_compile_options(
        /FC  # Full path in __FILE__
        /W3  # Warning level 3
    )

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        add_compile_options(/EHa)  # Exception handling
    else()
        add_compile_options(
            /EHsc  # Exception handling
            /O2    # Optimization
        )
    endif()
endif()
