-- local sceneManager = require('sceneManager');
-- local graphics = require('graphics')
-- local scene = sceneManager:new()

local background = graphics.newImage("art/intrface/mainmenu.frm")

--local function backgroundClickListener(event)
local function backgroundClickListener()
    print("click handled")
    --print(event.x)
    --print(event.y)
    --print(event.name)
end

background:addEventListener("click", backgroundClickListener)

scene.add(background)

-- return scene
