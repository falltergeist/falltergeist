if(WIN32)
    install(TARGETS falltergeist RUNTIME DESTINATION .)
    install(DIRECTORY data DESTINATION .)

    #MinGW runtime
    if(MINGW)
        get_filename_component(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} PATH )
        set(dep_files ${dep_files} "${MINGW_BIN_PATH}/libwinpthread-*.dll")
        set(dep_files ${dep_files} "${MINGW_BIN_PATH}/libgcc_s_*.dll")
        set(dep_files ${dep_files} "${MINGW_BIN_PATH}/libstdc++-*.dll")
    endif()

    #dependencies
    install(DIRECTORY $<TARGET_FILE_DIR:falltergeist>/
        DESTINATION .
        FILES_MATCHING PATTERN "*.dll")
endif()
