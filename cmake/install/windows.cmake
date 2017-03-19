#
# Copyright 2012-2016 Falltergeist Developers.
#
# This file is part of Falltergeist.
#
# Falltergeist is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Falltergeist is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
#

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
