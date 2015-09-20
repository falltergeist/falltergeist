--
-- Copyright 2012-2015 Falltergeist Developers.
--
-- This file is part of Falltergeist.
--
-- Falltergeist is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- Falltergeist is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
--

--
-- Base Lua State class
--

-- module/class table
local State = class "State"

State:wrapEngineClass(game.State)

function State:initialize()
    self.obj = game.State.pushNew(self)
end



--
-- GLOBAL definitions
--

enum = enum or {}
enum.TEXT_ALIGN = {
    CENTER = 2
}

enum.CURSOR = {
    BIG_ARROW = 1,
    WAIT = 21,
    HAND = 22
}


return State