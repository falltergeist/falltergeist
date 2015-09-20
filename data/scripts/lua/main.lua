--[[

    Main entry point for scripting subsystem.

    Create States and push them to state stack from here.

]]--

-- setting up package path
package.path = "./data/scripts/lua/?.lua;" .. package.path

-- require modules
require("global")
local MainMenu = require("state.MainMenu")

-- initialize game
MainMenu:new()
