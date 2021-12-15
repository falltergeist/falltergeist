-- local sceneManager = require('sceneManager');
-- local graphics = require('graphics')
-- local scene = sceneManager:new()

local function buttonClickListener(event)
    print(event.x)
    print(event.y)
    print(event.name)
    print(event.target)
    local button = event.target;
    button.x = button.x + 30
end

local function createButton(x, y)
    local button = graphics.newImage("art/intrface/menuup.frm")
    print(button)
    print(button.x)
    print(button.y)
    button.x = x
    button.y = y
    button:addEventListener("click", buttonClickListener)

    print(button)
    return button
end

local background = graphics.newImage("art/intrface/mainmenu.frm")

local introButton = createButton(30, 19)
local newGameButton = createButton(30, 19 + 41)

scene.add(background)
scene.add(introButton)
scene.add(newGameButton)

-- return scene
