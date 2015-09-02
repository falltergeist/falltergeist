enum = {
    TEXT_ALIGN = {
        CENTER = 2
    },

    CURSOR = {
        BIG_ARROW = 1,
        WAIT = 21,
        HAND = 22
    }
}

-- main menu state object
mainMenu = {}
-- obj is a C++ object
mainMenu.obj = game.State(mainMenu)

function MenuRedCircleButton(x, y)
    return game.ui.ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", "sound/sfx/ib1lu1x1.acm", "sound/sfx/ib1p1xx1.acm",  x or 0, y or 0)
end

function mainMenu:init()
    self.obj.modal = true
    self.obj.fullscreen = true

    game.mouse.cursor = enum.CURSOR.BIG_ARROW
    game.mouse.x = 400
    game.mouse.y = 400

    local background = game.ui.Image("art/intrface/mainmenu.frm")
    -- Buttons
    local introButton    = MenuRedCircleButton(30, 19);
    local newGameButton  = MenuRedCircleButton(30, 19 + 41);
    local loadGameButton = MenuRedCircleButton(30, 19 + 41*2);
    local settingsButton = MenuRedCircleButton(30, 19 + 41*3);
    local creditsButton  = MenuRedCircleButton(30, 19 + 41*4);
    local exitButton     = MenuRedCircleButton(30, 19 + 41*5);

    -- Labels
    --font = game.resourceManager.getFont("font4.aaf", 0xb89c28ff)

    local introLabel = game.ui.TextArea(game.translate("intro", "mainmenu"), 50, 20)
    --introLabel.font = font
    -- introLabel.width = 150
    introLabel.horizontalAlign = enum.TEXT_ALIGN.CENTER


    self.obj:addUI(background)
    self.obj:addUI(introButton)
    self.obj:addUI(newGameButton)
    self.obj:addUI(loadGameButton)
    self.obj:addUI(settingsButton)
    self.obj:addUI(creditsButton)
    self.obj:addUI(exitButton)

    self.obj:addUI(introLabel)

end

function mainMenu:think()
end

-- event is C++ object
function mainMenu:handle(event)
    if (event.name == "mousedown") then
        game.getInstance():quit()
    end
end

function mainMenu:render()

end


do return mainMenu end