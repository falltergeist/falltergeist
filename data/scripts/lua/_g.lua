--[[

    Main entry point for scripting subsystem.

    Create your states and push them to state stack from here.

]]--

dofile("data/scripts/lua/state/mainmenu.lua")


game.getInstance():setState(mainMenu.obj)
