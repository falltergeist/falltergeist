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

-- requires section
local State = require("state.State")
local Image = require("ui.Image")
local ImageButton = require("ui.ImageButton")
local TextArea = require("ui.TextArea")


-- class/module table
local MainMenu = State:subclass "MainMenu"

function MainMenu:RedCircleButton(x, y)
    return ImageButton:new(self, "art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", "sound/sfx/ib1lu1x1.acm", "sound/sfx/ib1p1xx1.acm",  x or 0, y or 0)
end

function MainMenu:initialize()
    State.initialize(self)

    self.modal = true
    self.fullscreen = true

    game.mouse.cursor = enum.CURSOR.BIG_ARROW
    game.mouse.position = Point(400, 400)

    -- background
    Image:new(self, "art/intrface/mainmenu.frm")

    -- Buttons
    local introButton    = self:RedCircleButton(30, 19);
    local newGameButton  = self:RedCircleButton(30, 19 + 41);
    local loadGameButton = self:RedCircleButton(30, 19 + 41*2);
    local settingsButton = self:RedCircleButton(30, 19 + 41*3);
    local creditsButton  = self:RedCircleButton(30, 19 + 41*4);
    local exitButton     = self:RedCircleButton(30, 19 + 41*5);

    -- Labels
    --font = game.resourceManager.getFont("font4.aaf", 0xb89c28ff)

    self.introLabel = TextArea:new(self, game.translate("intro", "mainmenu"), 50, 20)

    --introLabel.font = font
    -- introLabel.width = 150
    self.introLabel.horizontalAlign = enum.TEXT_ALIGN.CENTER

    game.renderer:fadeIn(0, 0, 0, 1000)
end

--function MainMenu:think()
--end

-- event is C++ object
function MainMenu:handle(event)
    if (event.name == "mousedown") then
        game.quit()
    end
end


-- return class table
return MainMenu
