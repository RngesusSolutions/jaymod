#-----------------------------------------------------------------
# Game Module Building
#-----------------------------------------------------------------

# Function to build a game module (cgame, qagame, ui)
function(build_game_module MODULE_NAME)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES DEFINITIONS INCLUDES LIBRARIES LINK_FLAGS)
    cmake_parse_arguments(MOD "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Create the module library
    add_library(${MODULE_NAME} MODULE ${MOD_SOURCES})

    # Set C standard to C90 for game modules (matching ETL)
    set_target_properties(${MODULE_NAME} PROPERTIES
        C_STANDARD 90
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
    )

    # Set C++ standard to C++11 for Omnibot integration
    set_target_properties(${MODULE_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    # Set output name with platform-specific naming
    set_target_properties(${MODULE_NAME} PROPERTIES
        PREFIX "${LIB_PREFIX}"
        OUTPUT_NAME "${MODULE_NAME}${LIB_SUFFIX}"
        SUFFIX "${LIB_EXT}"
    )

    # Set library destination
    set_target_properties(${MODULE_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/jaymod-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/jaymod-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    )

    # Add compile definitions
    if(MOD_DEFINITIONS)
        target_compile_definitions(${MODULE_NAME} PRIVATE ${MOD_DEFINITIONS})
    endif()

    # Add include directories
    if(MOD_INCLUDES)
        target_include_directories(${MODULE_NAME} PRIVATE ${MOD_INCLUDES})
    endif()

    # Link libraries
    if(MOD_LIBRARIES)
        target_link_libraries(${MODULE_NAME} PRIVATE ${MOD_LIBRARIES})
    endif()

    # Add link flags
    if(MOD_LINK_FLAGS)
        set_target_properties(${MODULE_NAME} PROPERTIES
            LINK_FLAGS "${MOD_LINK_FLAGS}"
        )
    endif()

    # Platform-specific settings
    if(UNIX AND NOT APPLE)
        # Linux: Set RPATH for finding libraries
        set_target_properties(${MODULE_NAME} PROPERTIES
            INSTALL_RPATH "$ORIGIN"
            BUILD_WITH_INSTALL_RPATH TRUE
        )

        # Strip symbols in release builds
        if(CMAKE_BUILD_TYPE MATCHES "Release")
            add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${MODULE_NAME}>
                COMMENT "Stripping ${MODULE_NAME}"
            )
        endif()
    elseif(WIN32)
        # Windows: Static linking of MinGW runtimes is handled in platform flags
        if(MINGW)
            # Strip symbols in release builds
            if(CMAKE_BUILD_TYPE MATCHES "Release")
                add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${MODULE_NAME}>
                    COMMENT "Stripping ${MODULE_NAME}"
                )
            endif()
        endif()
    endif()

    message(STATUS "Configured module: ${MODULE_NAME} -> ${MODULE_NAME}${LIB_SUFFIX}${LIB_EXT}")
endfunction()
