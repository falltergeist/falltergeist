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
local input = require("input")


-- class/module table
local MainMenu = State:subclass "MainMenu"

function MainMenu:LittleRedButton(x, y)
    return ImageButton:new(self, "art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", "sound/sfx/ib1lu1x1.acm", "sound/sfx/ib1p1xx1.acm",  x or 0, y or 0)
end

function MainMenu:BigMenuButton(x, y)
    return ImageButton:new(self, "art/intrface/menuup.frm", "art/intrface/menudown.frm", "sound/sfx/nmselec1.acm", "sound/sfx/nmselec0.acm",  x or 0, y or 0)
end

function MainMenu:BigLabel(textId, x, y)
    local ta = TextArea:new(self, game._t(enum.MSG_FILE.MISC, textId), x or 0, y or 0)
    ta:setFont("font4.aaf", 0xb89c28ff)
    ta.size = Size(150, 0)
    ta.horizontalAlign = enum.TEXT_ALIGN.CENTER
    return ta
end


function MainMenu:_doIntro()
    self:fadeOut(function()
        game.state.Movie.pushNew(17)
        game.state.Movie.pushNew(1)
    end)
end

function MainMenu:_doNewGame()
    self:fadeOut(function()
        game.state.NewGame.pushNew()
    end)
end

function MainMenu:_doLoadGame()
    self:fadeOut(function()
        game.state.LoadGame.pushNew()
    end)
end

function MainMenu:_doSettings()
    game.state.SettingsMenu.pushNew()
end

function MainMenu:_doCredits()
    self:fadeOut(function()
        game.state.Credits.pushNew()
    end)
end

function MainMenu:_doExit()
    self:fadeOut(function()
        game.mixer:stopMusic()
        game.quit()
    end)
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
    local introButton    = self:BigMenuButton(30, 19);
    local newGameButton  = self:BigMenuButton(30, 19 + 41);
    local loadGameButton = self:BigMenuButton(30, 19 + 41*2);
    local settingsButton = self:BigMenuButton(30, 19 + 41*3);
    local creditsButton  = self:BigMenuButton(30, 19 + 41*4);
    local exitButton     = self:BigMenuButton(30, 19 + 41*5);

    -- Labels
    self:BigLabel( 9, 50, 20) -- intro
    self:BigLabel(10, 50, 20 + 41) -- new game
    self:BigLabel(11, 50, 20 + 41*2) -- load game
    self:BigLabel(12, 50, 20 + 41*3) -- options
    self:BigLabel(13, 50, 20 + 41*4) -- credits
    self:BigLabel(14, 50, 20 + 41*5) -- exit

    -- Button click handlers
    local this = self
    introButton.obj:addEventHandler("mouseleftclick", function() this:_doIntro() end)
    newGameButton.obj:addEventHandler("mouseleftclick", function() this:_doNewGame() end)
    loadGameButton.obj:addEventHandler("mouseleftclick", function() this:_dodoLoadGame() end)
    settingsButton.obj:addEventHandler("mouseleftclick", function() this:_doSettings() end)
    creditsButton.obj:addEventHandler("mouseleftclick", function() this:_doCredits() end)
    exitButton.obj:addEventHandler("mouseleftclick", function() this:_doExit() end)
end

function MainMenu:onActivate()
    self:fadeIn()
    game.mixer:playACMMusic("07desert.acm", true)
end

function MainMenu:onKeyDown(event)
    local key = event.keyCode
    if key == input.SDLK_e or key == input.SDLK_ESCAPE then
        self:_doExit()
    elseif key == input.SDLK_n then
        self:_doNewGame()
    elseif key == input.SDLK_l then
        self:_doLoadGame()
    elseif key == input.SDLK_i then
        self:_doIntro()
    elseif key == input.SDLK_c then
        self:_doCredits()
    elseif key == input.SDLK_o then
        self:_doSettings()
    end
end

--function MainMenu:think()
--end

-- return class table
return MainMenu
