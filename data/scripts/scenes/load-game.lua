local sceneManager = require("sceneManager")
local graphics = require("graphics")

local LoadGameScene = {}
LoadGameScene.__index = LoadGameScene
setmetatable(LoadGameScene, {__index = sceneManager.Scene})

function LoadGameScene:new()
    local self = setmetatable({}, LoadGameScene)

    local background = graphics.newSprite("art/intrface/lsgame.frm")

    self:addEventHandler("mouse_up", function(event)
        sceneManager.replaceWith("main-menu")
    end)

    return self
end

return LoadGameScene:new()
