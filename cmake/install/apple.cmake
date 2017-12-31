#
# Copyright 2012-2018 Falltergeist Developers.
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

if(APPLE)
  configure_file(package/osx/Info.plist.in package/osx/Info.plist)
  configure_file(package/osx.sh.in package/osx.sh)

add_custom_command(
    OUTPUT Falltergeist.dmg
    COMMAND sh ./package/osx.sh
  )
  add_custom_target(dmg DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Falltergeist.dmg)
endif()
