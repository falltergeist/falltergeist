-- local sceneManager = require('sceneManager');
-- local graphics = require('graphics')
-- local scene = sceneManager:new()

local function createButton(x, y, name)
    local button = {}
    button.name = name

    function button:onClick()
        print('Button clicked: ', self.name)
        self.image.x = self.image.x + 30
    end

    button.image = graphics.newImage("art/intrface/menuup.frm")
    button.image.x = x
    button.image.y = y
    button.image:addEventListener("click", function() button:onClick() end)

    return button
end

local background = graphics.newImage("art/intrface/mainmenu.frm")

local introButton = createButton(30, 19, "Intro")
local newGameButton = createButton(30, 19 + 41, "New game")

scene.add(background)
scene.add(introButton.image)
scene.add(newGameButton.image)

-- return scene
