# Copyright (c) 2013 Martin Felis &lt;martin@fysx.org&gt;
# License: Public Domain (Unlicense: http://unlicense.org/)
#
# Try to find Lua or LuaJIT depending on the variable LUA_USE_LUAJIT.
# Sets the following variables:
#   Lua_FOUND
#   LUA_INCLUDE_DIR
#   LUA_LIBRARY
#
# Use it in a CMakeLists.txt script as:
#
#   OPTION (LUA_USE_LUAJIT "Use LuaJIT instead of default Lua" OFF)
#   UNSET(Lua_FOUND CACHE)
#   UNSET(LUA_INCLUDE_DIR CACHE)
#   UNSET(LUA_LIBRARY CACHE)
#   FIND_PACKAGE (Lua REQUIRED)
 
SET (Lua_FOUND FALSE)
     
SET (LUA_INTERPRETER_TYPE "")
     
IF (LUA_USE_LUAJIT)
    SET (LUA_INTERPRETER_TYPE "LuaJIT")
    SET (LUA_LIBRARY_NAME luajit-5.1)
    SET (LUA_INCLUDE_DIRS /usr/include/luajit-2.0 /usr/local/include/luajit-2.0)
ELSE (LUA_USE_LUAJIT)
    SET (LUA_INTERPRETER_TYPE "Lua")
    SET (LUA_LIBRARY_NAME lua5.1)
    SET (LUA_INCLUDE_DIRS /usr/include/lua5.1 /usr/local/include/lua5.1)
ENDIF(LUA_USE_LUAJIT)
     
FIND_PATH (LUA_INCLUDE_DIR lua.h ${LUA_INCLUDE_DIRS} )
FIND_LIBRARY (LUA_LIBRARY NAMES ${LUA_LIBRARY_NAME} PATHS /usr/lib /usr/local/lib)
     
IF (LUA_INCLUDE_DIR AND LUA_LIBRARY)
    SET (Lua_FOUND TRUE)
ENDIF (LUA_INCLUDE_DIR AND LUA_LIBRARY)
          
INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (Lua  DEFAULT_MSG LUA_LIBRARY LUA_INCLUDE_DIR)
     
MARK_AS_ADVANCED (LUA_INCLUDE_DIR LUA_LIBRARY)
