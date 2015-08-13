enum = {
    BUTTON_TYPE = {
        MENU_RED_CIRCLE = 3
    },

    TEXT_ALIGN = {
        CENTER = 2
    }
}


-- state is C++ object
init = function(state)
    state.modal = true
    state.fullscreen = true

    background = game.ui.Image("art/intrface/mainmenu.frm")

    -- Buttons
    introButton    = game.ui.ImageButton(enum.BUTTON_TYPE.MENU_RED_CIRCLE, 30, 19);
    newGameButton  = game.ui.ImageButton(enum.BUTTON_TYPE.MENU_RED_CIRCLE, 30, 19 + 41);
    loadGameButton = game.ui.ImageButton(enum.BUTTON_TYPE.MENU_RED_CIRCLE, 30, 19 + 41*2);
    settingsButton = game.ui.ImageButton(enum.BUTTON_TYPE.MENU_RED_CIRCLE, 30, 19 + 41*3);
    creditsButton  = game.ui.ImageButton(enum.BUTTON_TYPE.MENU_RED_CIRCLE, 30, 19 + 41*4);
    exitButton     = game.ui.ImageButton(enum.BUTTON_TYPE.MENU_RED_CIRCLE, 30, 19 + 41*5);
    
    -- Labels
    --font = game.resourceManager.getFont("font4.aaf", 0xb89c28ff)

    introLabel = game.ui.TextArea(game.translate("intro", "mainmenu"), 50, 20)
    --introLabel.font = font
    introLabel.width = 150
    introLabel.horizontalAlign = enum.TEXT_ALIGN.CENTER    


    state:addUI(background)
    state:addUI(introButton)
    state:addUI(newGameButton)
    state:addUI(loadGameButton)
    state:addUI(settingsButton)
    state:addUI(creditsButton)
    state:addUI(exitButton)

    state:addUI(introLabel)

end

-- state is C++ object
think = function(state)
end

-- state is C++ object
-- event is C++ object
handle = function(state, event)
    --print(event.name)
end

-- state is C++ object
render = function(state)
end
