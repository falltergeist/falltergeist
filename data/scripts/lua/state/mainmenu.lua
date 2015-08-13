ImageButton = {
    TYPE_MENU_RED_CIRCLE = 3
}


-- state is C++ object
init = function(state)
    state.modal = true
    state.fullscreen = true

    background = game.ui.Image("art/intrface/mainmenu.frm")

    introButton    = game.ui.ImageButton(ImageButton.TYPE_MENU_RED_CIRCLE, 30, 19);
    newGameButton  = game.ui.ImageButton(ImageButton.TYPE_MENU_RED_CIRCLE, 30, 19 + 41);
    loadGameButton = game.ui.ImageButton(ImageButton.TYPE_MENU_RED_CIRCLE, 30, 19 + 41*2);
    settingsButton = game.ui.ImageButton(ImageButton.TYPE_MENU_RED_CIRCLE, 30, 19 + 41*3);
    creditsButton  = game.ui.ImageButton(ImageButton.TYPE_MENU_RED_CIRCLE, 30, 19 + 41*4);
    exitButton     = game.ui.ImageButton(ImageButton.TYPE_MENU_RED_CIRCLE, 30, 19 + 41*5);

    state:addUI(background)
    state:addUI(introButton)
    state:addUI(newGameButton)
    state:addUI(loadGameButton)
    state:addUI(settingsButton)
    state:addUI(creditsButton)
    state:addUI(exitButton)

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
