local sceneManager = require("sceneManager")
local graphics = require("graphics")

local MainMenuScene = {}
MainMenuScene.__index = MainMenuScene
setmetatable(MainMenuScene, {__index = sceneManager.Scene})

function MainMenuScene:new()
    local self = setmetatable({}, MainMenuScene)

    local background = graphics.newSprite("art/intrface/mainmenu.frm")

    self:addEventHandler("mouse_up", function(event)
        sceneManager.replaceWith("settings")
    end)

    return self
end

return MainMenuScene:new()
