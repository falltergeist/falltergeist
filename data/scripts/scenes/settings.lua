local sceneManager = require("sceneManager")
local graphics = require("graphics")

local SettingsScene = {}
SettingsScene.__index = SettingsScene
setmetatable(MainMenuScene, {__index = sceneManager.Scene})

function SettingsScene:new()
    local self = setmetatable({}, SettingsScene)

    local background = graphics.newSprite("art/intrface/prefscrn.frm")

    self:addEventHandler("mouse_up", function(event)
        sceneManager.replaceWith("load-game")
    end)

    return self
end

return SettingsScene:new()
