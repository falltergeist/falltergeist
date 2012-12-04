# ${SDL_FOUND}
# ${SDL_LIBRARY}
# ${SDL_INCLUDE_DIR}
#
find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
    message(SEND_ERROR "Failed to find SDL")
    return()
else()
    include_directories(${SDL_INCLUDE_DIR})
endif()