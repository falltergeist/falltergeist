#
# Copyright 2012-2014 Falltergeist Developers.
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

FIND_PATH(LIBFALLTERGEIST_INCLUDE_DIR 
		libfalltergeist.h
	HINTS
		ENV LIBFALLTERGEIST_DIR
    PATH_SUFFIXES 
		include
		include/falltergeist
	PATHS
		~/libfalltergeist
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

FIND_LIBRARY(LIBFALLTERGEIST_LIBRARY 
		falltergeist 
	PATH_SUFFIXES
		dynamic
		lib
		${VC_LIB_PATH_SUFFIX}
		~/libfalltergeist
)

set(LIBFALLTERGEIST_LIBRARIES ${LIBFALLTERGEIST_LIBRARY})
set(LIBFALLTERGEIST_INCLUDE_DIRS ${LIBFALLTERGEIST_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBFALLTERGEIST
                                  REQUIRED_VARS LIBFALLTERGEIST_LIBRARIES LIBFALLTERGEIST_INCLUDE_DIR)

mark_as_advanced(LIBFALLTERGEIST_LIBRARY LIBFALLTERGEIST_INCLUDE_DIR)
