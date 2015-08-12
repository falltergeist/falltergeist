# The MIT License (MIT)
#
# Copyright (c) 2015 Falltergeist developers
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Sets the following variables:
#   LUA_FOUND
#   LUA_INCLUDE_DIR
#   LUA_LIBRARY
#
 
if(Lua_FIND_VERSION_MAJOR AND Lua_FIND_VERSION_MINOR)
    set(LUA_SUFFIXES "${Lua_FIND_VERSION_MAJOR}${Lua_FIND_VERSION_MINOR}"
                     "${Lua_FIND_VERSION_MAJOR}.${Lua_FIND_VERSION_MINOR}"
                     "-${Lua_FIND_VERSION_MAJOR}.${Lua_FIND_VERSION_MINOR}")
else(Lua_FIND_VERSION_MAJOR AND Lua_FIND_VERSION_MINOR)
    set(LUA_SUFFIXES "51"
                     "5.1"
                     "-5.1"
                     "52"
                     "5.2"
                     "-5.2")
endif(Lua_FIND_VERSION_MAJOR AND Lua_FIND_VERSION_MINOR)

set(LUA_INCLUDE_SEARCH_PATH include include/lua)
set(LUA_LIBRARY_SEARCH_PATH lua)

foreach(LUA_SUFFIX ${LUA_SUFFIXES})
    list(APPEND LUA_INCLUDE_SEARCH_PATH "include/lua${LUA_SUFFIX}")
    list(APPEND LUA_LIBRARY_SEARCH_PATH "lua${LUA_SUFFIX}")
endforeach(LUA_SUFFIX)

find_path(LUA_INCLUDE_DIR lua.h
    HINTS
        $ENV{LUA_DIR}
        PATH_SUFFIXES ${LUA_INCLUDE_SEARCH_PATH}
    PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr
        /usr/local
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
)

find_library(LUA_LIBRARY 
    NAMES ${LUA_LIBRARY_SEARCH_PATH}
    HINTS
        $ENV{LUA_DIR}
        PATH_SUFFIXES lib64 lib
    PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Lua REQUIRED_VARS LUA_LIBRARY LUA_INCLUDE_DIR)
mark_as_advanced(LUA_INCLUDE_DIR LUA_LIBRARY)
