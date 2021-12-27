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

local background = graphics.newSprite("art/intrface/mainmenu.frm")

local introButton = Button:new(30, 19 + 41*0)
local newGameButton = Button:new(30, 19 + 41*1)
local loadGameButton = Button:new(30, 19 + 41*2)
local settingsButton = Button:new(30, 19 + 41*3)
local creditsButton = Button:new(30, 19 + 41*4)
local exitButton = Button:new(30, 19 + 41*5)

local introButtonLabel = Text:new(50, 20 + 41*0, "INTRO")
local newGameButtonLabel = Text:new(50, 20 + 41*1, "NEW GAME")
local loadGameButtonLabel = Text:new(50, 20 + 41*2, "LOAD GAME")
local optionsButtonLabel = Text:new(50, 20 + 41*3, "OPTIONS")
local creditsButtonLabel = Text:new(50, 20 + 41*4, "CREDITS")
local exitButtonLabel = Text:new(50, 20 + 41*5, "EXIT")

scene.add(background)
scene.add(introButton.image)
scene.add(newGameButton.image)

-- return scene
