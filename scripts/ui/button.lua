local Button = {}

function Button:new()
    local button = {}
    setmetatable(button, Button)
    self.__index = self
    self.pressed = false
    self.sprite = -- load from 2 frm files

    self.sprite:addEventHandler('mouse_in', function(event) self:onMouseIn(event) end)
    self.sprite:addEventHandler('mouse_out', function(event) self:onMouseOut(event) end)
    self.sprite:addEventHandler('mouse_down', function(event) self:onMouseDown(event) end)
    self.sprite:addEventHandler('mouse_up', function(event) self:onMouseUp(event) end)

    return button
end

function Button:debug()
    print(self)
end

function Button:onMouseIn(event)
    if event.left_button_pressed then
        self.pressed = true
        self.sprite.setFrame(pressed)
    end
end

function Button:onMouseOut(event)
    self.pressed = false
    self.sprite.setFrame(released)
end

function Button:onMouseDown(event)
    -- if event.button = left_button
    self.pressed = true
    self.sprite.setFrame(pressed)
end

function Button:onMouseUp(event)
    -- if event.button = left_button
    self.pressed = false
    self.sprite.setFrame(released)
end

return Button
