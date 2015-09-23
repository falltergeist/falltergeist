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

State:wrapEngineClass(game.state.State)

function State:initialize()
    self.obj = game.state.State.pushNew(self)
end

function State:fadeIn(func)
    self:fade(true, 0, 0, 0, 1000, func)
end

function State:fadeOut(func)
    self:fade(false, 0, 0, 0, 1000, func)
end

function State:fade(isIn, r, g, b, delay, func)
    if isIn then
        game.renderer:fadeIn(r, g, b, delay)
    else
        game.renderer:fadeOut(r, g, b, delay)
    end
    if type(func) == "function" then
        local this = self
        self.obj:addEventHandler("fadedone", function(...)
            this.obj:removeEventHandlers("fadedone")
            func(...)
        end)
    end
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

enum.MSG_FILE = {
    INVENTORY = 0,
    LOAD_SAVE = 1,
    OPTIONS = 2,
    MISC = 3,
    EDITOR = 4,
    TRAITS = 5,
    SKILLS = 6,
    STATS = 7,
    SKILLDEX = 8,
    DIALOG_BOX = 9,
    PROTO_ITEMS = 10,
}


return State