local graphics = require('graphics')

local Button = {}

function Button:new()
    local button = {}
    setmetatable(button, Button)

    -- 26 is the menu button image size
    self.buttonGroup = display.newGroup(26, 26)

    self.pressedImage = graphics.newImage('art/intrface/menudown.frm')
    -- position is relative to the group
    self.pressedImage.x = 0
    self.pressedImage.y = 0
    self.pressedImage:hide()
    self.buttonGroup:add(pressedImage)

    -- position is relative to the group
    self.releasedImage = graphics.newImage('art/intrface/menuup.frm')
    self.releasedImage.x = 0
    self.releasedImage.x = 0
    self.buttonGroup:add(releasedImage)

    -- It should react on whole display group if no hit mask is provided
    -- local hitMask = display.newHitmask('released_image.png')
    -- button:setHitMask(hitMask)

    self.buttonGroup:addEventHandler('mouse_down', function(event)
        -- show pressed
        -- hide released
    end)

    self.buttonGroup:addEventHandler('mouse_up', function(event)
        -- show released
        -- hide pressed
    end)

    return buttonGroup
end

function Button:debug()
    print(self)
end

function Button:onMouseIn(event)
    if event.left_button_pressed then
        self.pressed = true
    end
end

function Button:onMouseOut(event)
    self.pressed = false
end

function Button:onMouseDown(event)
    -- if event.button = left_button
    self.pressed = true
    self.imageReleased:hide()
    self.imagePressed:show()
end

function Button:onMouseUp(event)
    -- if event.button = left_button
    self.pressed = false
    self.imageReleased:show()
    self.imagePressed:hide()
end

function Button:onMouseMove(event)
end

return Button
