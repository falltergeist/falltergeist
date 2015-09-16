--[[

    Main entry point for scripting subsystem.

    Create States and push them to state stack from here.

]]--

-- setting up package path
package.path = "./data/scripts/lua/?.lua;" .. package.path

require("state.mainmenu")


game.setState(mainMenu.obj)
