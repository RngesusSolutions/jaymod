#-----------------------------------------------------------------
# 32-bit Cross-Compilation Support
#-----------------------------------------------------------------

if(CROSS_COMPILE32)
    message(STATUS "Enabling 32-bit cross-compilation")

    # Check if we're on a 64-bit system
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Force 32-bit
        set(CMAKE_SIZEOF_VOID_P 4 CACHE STRING "Size of void pointer" FORCE)

        # Set processor type
        if(WIN32)
            set(CMAKE_SYSTEM_PROCESSOR "x86" CACHE STRING "System processor" FORCE)
        else()
            set(CMAKE_SYSTEM_PROCESSOR "i386" CACHE STRING "System processor" FORCE)
        endif()

        # Add -m32 flag for Unix compilers
        if(UNIX)
            # Replace -m64 with -m32 if present, otherwise add -m32
            if(CMAKE_C_FLAGS MATCHES "-m64")
                string(REPLACE "-m64" "-m32" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
            else()
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
            endif()

            if(CMAKE_CXX_FLAGS MATCHES "-m64")
                string(REPLACE "-m64" "-m32" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
            else()
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
            endif()

            if(CMAKE_EXE_LINKER_FLAGS MATCHES "-m64")
                string(REPLACE "-m64" "-m32" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
            else()
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
            endif()

            if(CMAKE_SHARED_LINKER_FLAGS MATCHES "-m64")
                string(REPLACE "-m64" "-m32" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
            else()
                set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
            endif()

            # Make flags persistent
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "C flags" FORCE)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXX flags" FORCE)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING "Linker flags" FORCE)
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}" CACHE STRING "Shared linker flags" FORCE)
        endif()

        message(STATUS "Cross-compiling 32-bit on 64-bit system")
    endif()
endif()
