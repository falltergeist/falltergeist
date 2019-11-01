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
    file(GLOB dep_files ${dep_files} "${CMAKE_BINARY_DIR}/bin/*.dll" "${CMAKE_FIND_ROOT_PATH}/bin/*.dll")
    install(FILES ${dep_files} DESTINATION .)
endif()
