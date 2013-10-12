#
# Copyright 2012-2013 Falltergeist Developers.
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
#

FIND_PATH(LIBFALLTERGEIST_INCLUDE_DIR libfalltergeist.h 
    PATHS
    ${CMAKE_SOURCE_DIR}/lib/libfalltergeist
    ~/libfalltergeist
)

FIND_LIBRARY(LIBFALLTERGEIST_LIBRARY falltergeist 
  PATHS
  ${CMAKE_SOURCE_DIR}/lib/libfalltergeist
  ~/libfalltergeist
)

IF(NOT LIBFALLTERGEIST_LIBRARY)
    MESSAGE("LIBFALLTERGEIST_LIBRARY not found... may be it must be compiled first")
ENDIF(NOT LIBFALLTERGEIST_LIBRARY)

IF(LIBFALLTERGEIST_INCLUDE_DIR)
    IF(LIBFALLTERGEIST_LIBRARY)
        SET(LIBFALLTERGEIST_FOUND "YES")
    ENDIF(LIBFALLTERGEIST_LIBRARY)
ENDIF(LIBFALLTERGEIST_INCLUDE_DIR)	
