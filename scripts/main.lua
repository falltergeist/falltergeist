-- local sceneManager = require('sceneManager');
-- local graphics = require('graphics')
-- local scene = sceneManager:new()

local function createButton(x, y, name)
    local button = Button.new()
    button.imagePressed.x = x
    button.imagePressed.y = y
    button.imageReleased.x = x
    button.imageReleased.y = y
    return button
end

local background = graphics.newImage("art/intrface/mainmenu.frm")

local introButton = createButton(30, 19, "Intro")
local newGameButton = createButton(30, 19 + 41, "New game")

scene.add(background)
scene.add(introButton.image)
scene.add(newGameButton.image)

-- return scene
