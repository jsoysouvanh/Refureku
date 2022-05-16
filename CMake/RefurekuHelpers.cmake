# Usage:
#    refureku_setup_target(
#       TARGET                  <target>
#       WORK_DIR                <working_directory>
#       RFK_SETTINGS_DIR_PATH   <path_to_refureku_settings_directory>
#       RFK_SETTINGS_FILENAME   <refureku_settings_filename>
#    )
#
# Arguments:
#   TARGET
#       Name of the target to setup.
#
#   WORK_DIR:
#       Working directory used to run the generator.
#       All path settings contained in the Refureku settings file can be defined relatively to WORK_DIR.
#       If unspecified, defaults to ${PROJECT_SOURCE_DIR}.
#
#   RFK_SETTINGS_DIR_PATH:
#       Path to directory containing the Refureku settings file.
#       If unspecified, defaults to "${WORK_DIR}".
#
#   RFK_SETTINGS_FILENAME:
#       Name of the Refureku settings file, including the extension.
#       If unspecified, defaults to "RefurekuSettings.toml".
function(refureku_setup_target)

    cmake_parse_arguments(
        FUNC_ARGS
        ""
        "TARGET;WORK_DIR;RFK_SETTINGS_DIR_PATH;RFK_SETTINGS_FILENAME"
        ""
        ${ARGN}
    )

    #### Check / Setup function parameters

    if (NOT FUNC_ARGS_TARGET)
        message(FATAL_ERROR "Missing TARGET argument")
    endif()

    if (NOT FUNC_ARGS_WORK_DIR)
        set(FUNC_ARGS_WORK_DIR ${PROJECT_SOURCE_DIR})
    endif()

    if (NOT FUNC_ARGS_RFK_SETTINGS_DIR_PATH)
        set(FUNC_ARGS_RFK_SETTINGS_DIR_PATH "${FUNC_ARGS_WORK_DIR}")
    endif()

    if (NOT FUNC_ARGS_RFK_SETTINGS_FILENAME)
        set(FUNC_ARGS_RFK_SETTINGS_FILENAME "RefurekuSettings.toml")
    endif()

    #### Link TARGET against Refureku
    
    target_link_libraries(${FUNC_ARGS_TARGET} PUBLIC Refureku)

    #### Setup generator

    add_custom_target(RunRefurekuGenerator
                        WORKING_DIRECTORY ${FUNC_ARGS_WORK_DIR}
                        COMMAND RefurekuGenerator "${FUNC_ARGS_RFK_SETTINGS_DIR_PATH}/${FUNC_ARGS_RFK_SETTINGS_FILENAME}") 

    add_dependencies(${FUNC_ARGS_TARGET} RunRefurekuGenerator)

endfunction()